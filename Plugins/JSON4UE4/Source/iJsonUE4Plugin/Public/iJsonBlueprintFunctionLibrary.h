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
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Dom/JsonObject.h"
#include "iJsonBlueprintFunctionLibrary.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Log_iJsonBlueprintFunctionLibrary, Log, All);

UCLASS()
class UiJsonBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/*UFUNCTION(BlueprintCallable, meta = (DisplayName = "Make One Instance of iUE4Threader"), Category = "YeHaike|iThread|iUE4Threader")
	static AiUE4Threader* MakeInstanceOfiUE4Threader(FString In_Name, TScriptInterface<IiUE4ThreaderDelegate> In_Delegate);*/

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create iJsonObject", Keywords = "Create iJsonObject"), Category = "YeHaike|iJson|iJsonBlueprintFunctionLibrary")
	static UiJsonObject* CreateiJsonObject(UObject* Outer);

public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LoadStringFromFile"), Category = "YeHaike|iJson|iJsonBlueprintFunctionLibrary")
	static	bool LoadStringFromFile(const FString& FileName, FString& StringFromFile, FText& OutFailReason);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LoadJsonStringFromFile"), Category = "YeHaike|iJson|iJsonBlueprintFunctionLibrary")
	static	bool LoadJsonStringFromFile(const FString& FileName, FString& JsonStringFromFile, UiJsonObject*& iJsonObject, FText& OutFailReason);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetJsonObjectFromJsonString"), Category = "YeHaike|iJson|iJsonBlueprintFunctionLibrary")
	static	bool GetJsonObjectFromJsonString(const FString& JsonString, UiJsonObject*& iJsonObject, FText& OutFailReason);

	/**Get line break string(like "\r\n")*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetStringOfLineBreak"), Category = "YeHaike|iJson|iJsonBlueprintFunctionLibrary")
	static	FString GetStringOfLineBreak()
	{
		return "\r\n";
	}

	/**Get Tab string(like "	")*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetStringOfTabs_01"), Category = "YeHaike|iJson|iJsonBlueprintFunctionLibrary")
	static	FString GetStringOfTabs_01()
	{
		return "	";
	}

	/**Get Tab string(like "\t")*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetStringOfTabs_02"), Category = "YeHaike|iJson|iJsonBlueprintFunctionLibrary")
	static	FString GetStringOfTabs_02()
	{
		return "\t";
	}

	/**
	* Returns the directory the root configuration files are located.
	*
	* @return root config directory
	*/
	UFUNCTION(BlueprintPure, Category = "YeHaike|iJson|iJsonBlueprintFunctionLibrary|Path")
	static FString GetGameConfigDir();

	/**
	* Converts a relative path name to a fully qualified name relative to the process BaseDir().
	*/
	UFUNCTION(BlueprintPure, Category = "YeHaike|iJson|iJsonBlueprintFunctionLibrary|Path")
	static FString ConvertRelativePathToFull(const FString& InPath);

};
