// Fill out your copyright notice in the Description page of Project Settings.


#include "T_AssetTestActor.h"

// Sets default values
AT_AssetTestActor::AT_AssetTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AT_AssetTestActor::BeginPlay()
{
	Super::BeginPlay();
	x = 0;
#if PLATFORM_ANDROID
	//sot.setx(2);
#endif
	
}

// Called every frame
void AT_AssetTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	x += 1;
	UE_LOG(LogTemp, Warning, TEXT("x= %i \n"), x);
#if PLATFORM_ANDROID
	//int result = sot.test1(x);
	std::string name = "Tom";
	std::string result = get_greet(name);
	UE_LOG(LogTemp, Warning, TEXT("result of get_greet(Tom) = %s \n"), result.c_str());
#endif
	
}

