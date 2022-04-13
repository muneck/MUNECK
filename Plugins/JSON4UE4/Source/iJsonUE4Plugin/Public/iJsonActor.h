/*
*  Copyright (c) 2016-2018 YeHaike(841660657@qq.com).
*  All rights reserved.
*  @ Date : 2018/05/03
*
*/

#pragma once
#include "CoreMinimal.h"
#include "UObject/UnrealType.h"
#include "UObject/ObjectMacros.h"
#include "UObject/UnrealType.h"
#include "UObject/TextProperty.h"
#include "GameFramework/Actor.h"
#include "Dom/JsonObject.h"
#include "iJsonActor.generated.h"

class UiJsonObject;

UCLASS(ClassGroup = ActorsOfYeHaike, BlueprintType, Blueprintable, config = iConfigs, meta = (ShortTooltip = "AiJsonActor is used to process JSON String"))
class AiJsonActor : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Json, EditAnywhere, BlueprintReadWrite)
	FString NewJsonString;


public:
	TWeakObjectPtr< UiJsonObject > JsonObject;

public:	
	// Sets default values for this actor's properties
	AiJsonActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LoadStringFromFile"), Category = "YeHaike|iJson|iJsonActor")
	bool LoadStringFromFile(const FString& FileName, FString& StringFromFile, FText& OutFailReason);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LoadJsonStringFromFile"), Category = "YeHaike|iJson|iJsonActor")
	bool LoadJsonStringFromFile(const FString& FileName, FString& JsonStringFromFile, UiJsonObject*& iJsonObject, FText& OutFailReason);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetJsonObjectFromJsonString"), Category = "YeHaike|iJson|iJsonActor")
	bool GetJsonObjectFromJsonString(const FString& JsonString, UiJsonObject*& iJsonObject, FText& OutFailReason);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetJsonObjectFromSelfJsonString"), Category = "YeHaike|iJson|iJsonActor")
	bool GetJsonObjectFromSelfJsonString(UiJsonObject*& iJsonObject, FText& OutFailReason);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set iJsonObject"), Category = "YeHaike|iJson|iJsonActor")
	void SetiJsonObject(UiJsonObject* iJsonObject);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get iJsonObject"), Category = "YeHaike|iJson|iJsonActor")
	UiJsonObject*  GetiJsonObject();

	/**Get line break string(like "\r\n")*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetStringOfLineBreak"), Category = "YeHaike|iJson|iJsonActor")
	FString GetStringOfLineBreak()
	{
		return "\r\n";
	}

	/**Get Tab string(like "	")*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetStringOfTabs_01"), Category = "YeHaike|iJson|iJsonActor")
	FString GetStringOfTabs_01()
	{
		return "	";
	}

	/**Get Tab string(like "\t")*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetStringOfTabs_02"), Category = "YeHaike|iJson|iJsonActor")
	FString GetStringOfTabs_02()
	{
		return "\t";
	}
};
