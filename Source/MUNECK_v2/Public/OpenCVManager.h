// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "GameFramework/Actor.h"
#include "CoreMinimal.h"


//#include "opencv2/core.hpp"
#include "D:\programming\mediapipe\Google_Mediapipe_Hand_Tracking_dll-main\dll_use_example\Mediapipe_Hand_Tracking_Test\third\OpenCV\include\opencv2\core\core.hpp"

#include "MediaTexture.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Runtime/Engine/Classes/Engine/TextureRenderTarget2D.h"
#include "Components/SceneCaptureComponent2D.h"

//#include "opencv2/objdetect/objdetect.hpp"
//#include "opencv2/objdetect/detection_based_tracker.hpp"
//#include "opencv2/objdetect/objdetect_c.h"

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

//#include <opencv2/core/core.hpp> 

#include "DynamicModuleLoader.h"


#include "OpenCVManager.generated.h"



UCLASS()
class MUNECK_V2_API AOpenCVManager : public AActor
{
	GENERATED_BODY()
	typedef int (*Func_InitGraph)(const char* model_path);
	typedef int (*Func_Face_tracking)(float* gs,cv::Mat& Cap);
	typedef int(*Func_Release)();
	typedef int(*Func_Get)();
	
public:	
	// Sets default values for this actor's properties
	AOpenCVManager(const FObjectInitializer& ObjectInitializer);
	void* Init_Graph;
	void* Track_face;
	void* Release_Graph;
	Func_Get Get_Singleton;
	DynamicModuleLoaderSpace::DynamicModuleLoader dllLoader;
	FString dll_path;
	FString mediapipe_hand_tracking_model_path;
	float gestureRecognitionResult[10] = {};
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool DetectFace(cv::Mat CVTexture, FVector2D& OutPos);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Input)
		USceneComponent* rootComp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OpenCV)
		UStaticMeshComponent* Screen_Raw;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OpenCV)
		UStaticMeshComponent* Screen_Post;

	// The device ID opened by the Video Stream
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (ClampMin = 0, UIMin = 0))
		int32 CameraID;
	// The device ID opened by the Video Stream
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (ClampMin = 0, UIMin = 0))
		int32 VideoTrackID;
	// The rate at which the color data array and video texture is updated (in frames per second)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OpenCV, meta = (ClampMin = 0, UIMin = 0))
		float RefreshRate;
	// The refresh timer
	UPROPERTY(BlueprintReadWrite, Category = OpenCV)
		float RefreshTimer;
	UPROPERTY(BlueprintReadWrite, Category = OpenCV)
		FVector2D FacePos;

	// is the camera stream on
	UPROPERTY(BlueprintReadWrite, Category = Input)
		bool isStreamOpen;
	// The videos width and height (width, height)
	UPROPERTY(BlueprintReadWrite, Category = Input)
		FVector2D VideoSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OpenCV)
		float Brightness;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OpenCV)
		float Multiply;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OpenCV)
		float Turn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OpenCV)
		float Tilt;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OpenCV)
		float Nod;


	// Camera Media Player
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Input)
		UMediaPlayer* Camera_MediaPlayer;
	// Camera Media Texture
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Input)
		UMediaTexture* Camera_MediaTexture;

	// 8 bit Render Target (Pre Edit)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Materials)
		UTextureRenderTarget2D* Camera_RenderTarget;
	// Catches Back to player (Post Edit)

	// Material Camera raw Instance (Pre Edit)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Materials)
		UMaterialInstanceDynamic* Camera_MatRaw;
	// Draws OpenCV_Texture2D (Post Edit)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Materials)
		UMaterialInstanceDynamic* Camera_MatPost;

	// OpenCV Texture (Post Edit)
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = OpenCV)
		UTexture2D* Camera_Texture2D;
	// Color Data
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Data)
		TArray<FColor> ColorData;

	// Blueprint Event called every time the video frame is updated
	UFUNCTION(BlueprintImplementableEvent, Category = OpenCV)
		void OnNextVideoFrame();
	// reads the current video frame
	UFUNCTION(BlueprintCallable, Category = Data)
		bool ReadFrame(FVector2D Fpos);

	//OpenCV
	cv::Size cvSize;
	cv::Mat cvMat;
};
