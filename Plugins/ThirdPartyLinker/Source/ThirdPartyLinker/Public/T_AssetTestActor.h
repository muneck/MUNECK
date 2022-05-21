// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#if PLATFORM_ANDROID
#include <hello-greet.h>
#endif

#include "T_AssetTestActor.generated.h"
UCLASS()
class THIRDPARTYLINKER_API AT_AssetTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AT_AssetTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	int x;
#if PLATFORM_ANDROID
	//SharedObjTester sot;
#endif
	

};
