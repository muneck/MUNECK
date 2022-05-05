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
#include "UObject/Object.h"
#include "Dom/JsonObject.h"
#include "iJsonObject.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = "YeHaike|iJson|iJsonObject", BlueprintType, Blueprintable, config = iConfigs, meta = (ShortTooltip = "iJsonObject is used to store JSON."))
class UiJsonObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Json, EditAnywhere, BlueprintReadWrite)
	FString NewJsonString;

public:
	TSharedPtr< FJsonObject > JsonObject;


public:
	UiJsonObject();

public:

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TryGetNumberField"), Category = "YeHaike|iJson|iJsonObject")
	bool TryGetNumberField(const FString& FieldName, float& OutNumber);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TryGetStringField"), Category = "YeHaike|iJson|iJsonObject")
	bool TryGetStringField(const FString& FieldName, FString& OutString);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TryGetBoolField"), Category = "YeHaike|iJson|iJsonObject")
	bool TryGetBoolField(const FString& FieldName, bool& OutBool);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TryGetObjectField"), Category = "YeHaike|iJson|iJsonObject")
	bool TryGetObjectField(const FString& FieldName, UiJsonObject*& OutiJsonObject);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TryGetStringArrayField"), Category = "YeHaike|iJson|iJsonObject")
	bool TryGetStringArrayField(const FString& FieldName, TArray<FString>& OutArray);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TryGetNumberArrayField"), Category = "YeHaike|iJson|iJsonObject")
	bool TryGetNumberArrayField(const FString& FieldName, TArray<float>& OutArray);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TryGet iJsonObject ArrayField"), Category = "YeHaike|iJson|iJsonObject")
	bool TryGetJsonObjectArrayField(const FString& FieldName, TArray<UiJsonObject *>& OutArray);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ConstructJsonObjectFromSelfJsonString"), Category = "YeHaike|iJson|iJsonObject")
	bool ConstructJsonObjectFromSelfJsonString(FText& OutFailReason);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ConstructJsonObjectFromJsonString"), Category = "YeHaike|iJson|iJsonObject")
	bool ConstructJsonObjectFromJsonString(const FString& JsonString, FText& OutFailReason);
	// bool TryGetArrayField(const FString& FieldName, const TArray< TSharedPtr<FJsonValue> >*& OutArray);

};
