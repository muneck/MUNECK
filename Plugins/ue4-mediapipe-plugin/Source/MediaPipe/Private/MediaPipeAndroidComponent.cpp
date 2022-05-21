// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaPipeAndroidComponent.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif
//DEFINE_LOG_CATEGORY(LogMediaPipe);

// Sets default values for this component's properties
UMediaPipeAndroidComponent::UMediaPipeAndroidComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMediaPipeAndroidComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMediaPipeAndroidComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//void UMediaPipeAndroidComponent::GetFunctionHandler()
//{
//}

const FMediaPipeFaceRotation& UMediaPipeAndroidComponent::GetFaceStatusAndroid()
{ 
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID MethodGetTurn = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AAR_get_turn", "()F", false);
		float turn = FJavaWrapper::CallFloatMethod(Env, FJavaWrapper::GameActivityThis, MethodGetTurn);

		static jmethodID MethodGetTilt = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AAR_get_tilt", "()F", false);
		float tilt = FJavaWrapper::CallFloatMethod(Env, FJavaWrapper::GameActivityThis, MethodGetTilt);

		static jmethodID MethodGetNod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AAR_get_nod", "()F", false);
		float nod = FJavaWrapper::CallFloatMethod(Env, FJavaWrapper::GameActivityThis, MethodGetNod);
		
		static FMediaPipeFaceRotation Dum;
		Dum.Turn = turn;
		Dum.Tilt = tilt;
		Dum.Nod = nod;
		return Dum;
	}
	else {
		//UE_LOG(LogMediapipe, Error,TEXT("Android JavaEnv fail to get!"))
		static FMediaPipeFaceRotation Dum; 
		Dum.Turn = -0.114;
		Dum.Tilt = 0.114;
		Dum.Nod = -0.114;
		return Dum;
	}
	

#else
	
	static FMediaPipeFaceRotation Dum;
	Dum.Turn = -0.114;
	Dum.Tilt = 0.114;
	Dum.Nod = -0.114;
	return Dum;
	
#endif
}