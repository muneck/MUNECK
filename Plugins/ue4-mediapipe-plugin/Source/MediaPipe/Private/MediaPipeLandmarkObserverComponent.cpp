#include "MediaPipeLandmarkObserverComponent.h"
#include "MediaPipePipelineComponent.h"
#include "MediaPipeShared.h"
#include "DrawDebugHelpers.h"
#include <vector>

#if PLATFORM_WINDOWS
#include "mediapipe/framework/formats/landmark.pb.h"
#endif
using FMediaPipeLandmarkList = TArray<FMediaPipeLandmark>;

#if PLATFORM_WINDOWS
UMediaPipeLandmarkObserverComponent::UMediaPipeLandmarkObserverComponent()
{
}

struct LandmarkParser
{
	float MinVisibility = 0;
	float MinPresence = 0;
	int AxisX = 0;
	int AxisY = 1;
	int AxisZ = 2;
	FVector WorldScale = {1, 1, 1};

	template<typename TLandmark>
	void ParseLandmark(const TLandmark& Src, FMediaPipeLandmark& Dst)
	{
		Dst.Visibility = Src.visibility();
		Dst.Presence = Src.presence();

		if (Dst.Visibility >= MinVisibility && Dst.Presence >= MinPresence)
		{
			auto Pos = FVector(Src.x(), Src.y(), Src.z());
			Dst.Pos = Scale3D(ShuffleAxes(Pos, (int)AxisX, (int)AxisY, (int)AxisZ), WorldScale);
		}
	}

	template<typename TList>
	void ParseList(const TList& Src, FMediaPipeLandmarkList& Dst)
	{
		const int Count = Src.landmark_size();
		Dst.SetNum(Count);
		for (int i = 0; i < Count; ++i)
			ParseLandmark(Src.landmark(i), Dst[i]);
	}

	template<typename TMsg>
	void Parse(const TMsg& Src, TArray<FMediaPipeLandmarkList>& MultiLandmarks, int& Count)
	{
		Count = 1;
		Grow(MultiLandmarks, 1);
		ParseList(Src, MultiLandmarks[0]);
	}

	template<typename TMsg>
	void Parse(const std::vector<TMsg>& Src, TArray<FMediaPipeLandmarkList>& MultiLandmarks, int& Count)
	{
		Count = Src.size();
		Grow(MultiLandmarks, Count);
		for (int i = 0; i < Count; ++i)
			ParseList(Src[i], MultiLandmarks[i]);
	}
};

template<typename TList>
void Parse(LandmarkParser& Parser, IUmpObserver* Observer, TArray<FMediaPipeLandmarkList>& MultiLandmarks, int& Count)
{
	if (!UmpCompareType<TList>(Observer))
	{
		//PLUGIN_LOG(Error, TEXT("Invalid Landmark message"));
		return;
	}

	const auto& Message = UmpCastPacket<TList>(Observer->GetData()); //in the message lies the landmarks
	Parser.Parse(Message, MultiLandmarks, Count); // send the message to parser to parse the xyz into UE vectors.
}

// WARNING: executed in MediaPipe thread context!
void UMediaPipeLandmarkObserverComponent::OnUmpPacket(IUmpObserver* Observer)
{
	LandmarkParser Parser;
	Parser.MinVisibility = MinVisibility;
	Parser.MinPresence = MinPresence;
	Parser.AxisX = (int)AxisX;
	Parser.AxisY = (int)AxisY;
	Parser.AxisZ = (int)AxisZ;
	Parser.WorldScale = WorldScale;

	int InCount = 0;
	switch (LandmarkListType)
	{
		case EMediaPipeLandmarkListType::LandmarkList:					Parse<mediapipe::LandmarkList>(Parser, Observer, MultiLandmarks, InCount); break;
		case EMediaPipeLandmarkListType::NormalizedLandmarkList:		Parse<mediapipe::NormalizedLandmarkList>(Parser, Observer, MultiLandmarks, InCount); break;
		case EMediaPipeLandmarkListType::MultiLandmarkList:				Parse<std::vector<mediapipe::LandmarkList>>(Parser, Observer, MultiLandmarks, InCount); break;
		case EMediaPipeLandmarkListType::MultiNormalizedLandmarkList:	Parse<std::vector<mediapipe::NormalizedLandmarkList>>(Parser, Observer, MultiLandmarks, InCount); break;
		default: check(false); break;
	}

	NumDetections = InCount;
	UpdateTimestamp();
}

const TArray<FMediaPipeLandmark>& UMediaPipeLandmarkObserverComponent::GetLandmarkList(int ObjectId)
{
	if (ObjectId >= 0 && ObjectId < NumDetections)
	{
		return MultiLandmarks[ObjectId];
	}
	//PLUGIN_LOG(Error, TEXT("ObjectId out of range"));
	static FMediaPipeLandmarkList Dummy;
	return Dummy;
}

const FMediaPipeLandmark& UMediaPipeLandmarkObserverComponent::GetLandmark(int ObjectId, int LandmarkId)
{
	const auto& List = GetLandmarkList(ObjectId);
	if (LandmarkId >= 0 && LandmarkId < List.Num())
	{
		return List[LandmarkId];
	}
	//PLUGIN_LOG(Error, TEXT("LandmarkId out of range"));
	static FMediaPipeLandmark Dummy;
	return Dummy;
}


const FMediaPipeFaceRotation& UMediaPipeLandmarkObserverComponent::GetFaceStatus(int ObjectId)
{
	//const auto& List = GetLandmarkList(ObjectId);
	float turn = -GetLandmark(ObjectId, 33).Pos[0] + GetLandmark(ObjectId, 263).Pos[0];
	float tilt = atan((GetLandmark(ObjectId, 33).Pos[2] - GetLandmark(ObjectId, 263).Pos[2])/ (GetLandmark(ObjectId, 33).Pos[1] - GetLandmark(ObjectId, 263).Pos[1]))+3.1415926/2.0;
	float nod = - GetLandmark(ObjectId, 1).Pos[0] + GetLandmark(ObjectId, 168).Pos[0];
	
	static FMediaPipeFaceRotation Dum;
	Dum.Turn = turn;
	Dum.Tilt = tilt;
	Dum.Nod = nod;
	return Dum;
}


bool UMediaPipeLandmarkObserverComponent::TryGetLandmarkList(int ObjectId, TArray<FMediaPipeLandmark>& LandmarkList)
{
	if (ObjectId >= 0 && ObjectId < NumDetections)
	{
		LandmarkList = MultiLandmarks[ObjectId];
		return true;
	}
	return false;
}

bool UMediaPipeLandmarkObserverComponent::TryGetLandmark(int ObjectId, int LandmarkId, FMediaPipeLandmark& Landmark)
{
	if (ObjectId >= 0 && ObjectId < NumDetections)
	{
		const auto& List = MultiLandmarks[ObjectId];
		if (LandmarkId >= 0 && LandmarkId < List.Num())
		{
			Landmark = List[LandmarkId];
			return true;
		}
	}
	return false;
}

void UMediaPipeLandmarkObserverComponent::DrawDebugLandmarks(int ObjectId, const FTransform& Transform, float PrimitiveScale, FLinearColor Color)
{
	#if ENABLE_DRAW_DEBUG

	if (ObjectId >= 0 && ObjectId < NumDetections)
	{
		auto* World = GetWorld();
		const auto& List = MultiLandmarks[ObjectId];
		const int Count = List.Num();
		const auto RawColor = Color.ToFColor(false);

		for (int i = 0; i < Count; i++)
		{
			const auto& L = List[i];
			if ((L.Visibility > MinVisibility) && (L.Presence > MinPresence))
			{
				auto Pos = Transform.TransformPosition(L.Pos);
				DrawDebugPoint(World, Pos, PrimitiveScale, RawColor);
				//DrawDebugCoordinateSystem(World, Pos, FRotator::ZeroRotator, PrimitiveScale);
			}
		}
	}

	#endif
}
#elif PLATFORM_ANDROID
UMediaPipeLandmarkObserverComponent::UMediaPipeLandmarkObserverComponent()
{

}

//delete parser, no outside reference

void UMediaPipeLandmarkObserverComponent::OnUmpPacket(IUmpObserver* Observer)
{
	
}

const TArray<FMediaPipeLandmark>& UMediaPipeLandmarkObserverComponent::GetLandmarkList(int ObjectId)
{
	static FMediaPipeLandmarkList Dummy;
	return Dummy;
}
const FMediaPipeLandmark& UMediaPipeLandmarkObserverComponent::GetLandmark(int ObjectId, int LandmarkId)
{
	static FMediaPipeLandmark Dummy;
	return Dummy;
}
const FMediaPipeFaceRotation& UMediaPipeLandmarkObserverComponent::GetFaceStatus(int ObjectId)
{
	static FMediaPipeFaceRotation Dum;
	Dum.Turn = -0.114;
	Dum.Tilt = 0.114;
	Dum.Nod = -0.114;
	return Dum;
}
bool UMediaPipeLandmarkObserverComponent::TryGetLandmarkList(int ObjectId, TArray<FMediaPipeLandmark>& LandmarkList)
{
	return false;
}
bool UMediaPipeLandmarkObserverComponent::TryGetLandmark(int ObjectId, int LandmarkId, FMediaPipeLandmark& Landmark)
{
	return false;
}
void UMediaPipeLandmarkObserverComponent::DrawDebugLandmarks(int ObjectId, const FTransform& Transform, float PrimitiveScale, FLinearColor Color)
{
	return;
}
#endif