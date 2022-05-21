// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MediaPipeLandmarkObserverComponent.h" //for struct

#include "MediaPipeAndroidComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEDIAPIPE_API UMediaPipeAndroidComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMediaPipeAndroidComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Category = "MediaPipe", BlueprintCallable, BlueprintPure)
		const FMediaPipeFaceRotation& GetFaceStatusAndroid();

		
};
