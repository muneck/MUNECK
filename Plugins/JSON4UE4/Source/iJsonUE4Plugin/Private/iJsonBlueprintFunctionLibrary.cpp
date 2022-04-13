/*
*  Copyright (c) 2016-2018 YeHaike(841660657@qq.com).
*  All rights reserved.
*  @ Date : 2018/05/03
*
*/

#include "iJsonBlueprintFunctionLibrary.h"

#define LOCTEXT_NAMESPACE "iJsonBlueprintFunctionLibrary"
DEFINE_LOG_CATEGORY(Log_iJsonBlueprintFunctionLibrary);

UiJsonObject* UiJsonBlueprintFunctionLibrary::CreateiJsonObject(UObject* Outer)
{
	UiJsonObject* NewiJsonObject = NewObject<UiJsonObject>(Outer);
	return NewiJsonObject;
}

bool UiJsonBlueprintFunctionLibrary::LoadStringFromFile(const FString& FileName, FString& StringFromFile, FText& OutFailReason)
{
	FString FileContents;
	if (!FFileHelper::LoadFileToString(FileContents, *FileName))
	{
		OutFailReason = FText::Format(LOCTEXT("FailedToLoadStringFromFile", "Failed to load string from this file '{0}'"), FText::FromString(FileName));
		return false;
	}

	StringFromFile = FileContents;
	return true;
}


bool UiJsonBlueprintFunctionLibrary::LoadJsonStringFromFile(const FString& FileName, FString& JsonStringFromFile, UiJsonObject*& iJsonObject, FText& OutFailReason)
{
	FString FileContents;
	if (!FFileHelper::LoadFileToString(FileContents, *FileName))
	{
		OutFailReason = FText::Format(LOCTEXT("FailedToLoadJsonFile", "Failed to open Json file '{0}'"), FText::FromString(FileName));
		return false;
	}

	// Deserialize a Json object from the string
	TSharedPtr< FJsonObject > JsonObject_Temp;
	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(FileContents);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject_Temp) || !JsonObject_Temp.IsValid())
	{
		OutFailReason = FText::Format(LOCTEXT("FailedToReadJsonFile", "Failed to read Json file. {0}"), FText::FromString(Reader->GetErrorMessage()));
		return false;
	}

	JsonStringFromFile = FileContents;

	TWeakObjectPtr< UiJsonObject > tempJsonObject = NewObject<UiJsonObject>();
	(*tempJsonObject.Get()).JsonObject = JsonObject_Temp;
	(*tempJsonObject.Get()).NewJsonString = FileContents;
	iJsonObject = tempJsonObject.Get();

	// Parse it as a project descriptor
	return true;
}

bool UiJsonBlueprintFunctionLibrary::GetJsonObjectFromJsonString(const FString& JsonString, UiJsonObject*& iJsonObject, FText& OutFailReason)
{
	// Deserialize a Json object from the string
	TSharedPtr< FJsonObject > JsonObject_Temp;
	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(JsonString);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject_Temp) || !JsonObject_Temp.IsValid())
	{
		OutFailReason = FText::Format(LOCTEXT("FailedToGetJsonObjectFromJsonString", "Failed to get JsonObject from this JsonString. {0}"), FText::FromString(Reader->GetErrorMessage()));
		return false;
	}

	TWeakObjectPtr< UiJsonObject > tempJsonObject = NewObject<UiJsonObject>();
	(*tempJsonObject.Get()).JsonObject = JsonObject_Temp;
	(*tempJsonObject.Get()).NewJsonString = JsonString;
	iJsonObject = tempJsonObject.Get();

	// Parse it as a project descriptor
	return true;
}

FString UiJsonBlueprintFunctionLibrary::GetGameConfigDir()
{
	return FPaths::ProjectConfigDir();
}

FString UiJsonBlueprintFunctionLibrary::ConvertRelativePathToFull(const FString& InPath)
{
	return FPaths::ConvertRelativePathToFull(InPath);
}

#undef LOCTEXT_NAMESPACE