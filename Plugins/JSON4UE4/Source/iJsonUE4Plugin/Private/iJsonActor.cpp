/*
*  Copyright (c) 2016-2018 YeHaike(841660657@qq.com).
*  All rights reserved.
*  @ Date : 2018/05/03
*
*/

#include "iJsonActor.h"
#include "iJsonObject.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#define LOCTEXT_NAMESPACE "iJsonActor"
// Sets default values
AiJsonActor::AiJsonActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	JsonObject = nullptr;
	 
}

// Called when the game starts or when spawned
void AiJsonActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AiJsonActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


bool AiJsonActor::LoadStringFromFile(const FString& FileName, FString& StringFromFile, FText& OutFailReason)
{
	FString FileContents;
	if (!FFileHelper::LoadFileToString(FileContents, *FileName))
	{
		OutFailReason = FText::Format(LOCTEXT("FailedToLoadStringFromFile", "Failed to load string from this file '{0}'"), FText::FromString(FileName));
		return false;
	}

	StringFromFile = FileContents;
	NewJsonString = FileContents;
	return true;
}


bool AiJsonActor::LoadJsonStringFromFile(const FString& FileName, FString& JsonStringFromFile, UiJsonObject*& iJsonObject, FText& OutFailReason)
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
	NewJsonString = FileContents;

	TWeakObjectPtr< UiJsonObject > tempJsonObject = NewObject<UiJsonObject>();
	(*tempJsonObject.Get()).JsonObject = JsonObject_Temp;
	(*tempJsonObject.Get()).NewJsonString = FileContents;
	iJsonObject = tempJsonObject.Get();
	JsonObject = tempJsonObject;

	// Parse it as a project descriptor
	return true;
}

bool AiJsonActor::GetJsonObjectFromJsonString(const FString& JsonString, UiJsonObject*& iJsonObject, FText& OutFailReason)
{
	// Deserialize a Json object from the string
	TSharedPtr< FJsonObject > JsonObject_Temp;
	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(JsonString);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject_Temp) || !JsonObject_Temp.IsValid())
	{
		OutFailReason = FText::Format(LOCTEXT("FailedToGetJsonObjectFromJsonString", "Failed to get JsonObject from this JsonString. {0}"), FText::FromString(Reader->GetErrorMessage()));
		return false;
	}

	this->NewJsonString = JsonString;

	TWeakObjectPtr< UiJsonObject > tempJsonObject = NewObject<UiJsonObject>();
	(*tempJsonObject.Get()).JsonObject = JsonObject_Temp;
	(*tempJsonObject.Get()).NewJsonString = JsonString;
	iJsonObject = tempJsonObject.Get();
	JsonObject = tempJsonObject;

	// Parse it as a project descriptor
	return true;
}

bool AiJsonActor::GetJsonObjectFromSelfJsonString(UiJsonObject*& iJsonObject, FText& OutFailReason)
{
	return GetJsonObjectFromJsonString(NewJsonString, iJsonObject, OutFailReason);
}


void AiJsonActor::SetiJsonObject(UiJsonObject* iJsonObject)
{
	if (iJsonObject != nullptr&&JsonObject.IsValid())
	{
		(*JsonObject.Get()).JsonObject = iJsonObject->JsonObject;
		(*JsonObject.Get()).NewJsonString = iJsonObject->NewJsonString;
		NewJsonString = iJsonObject->NewJsonString;
	}
}

UiJsonObject*  AiJsonActor::GetiJsonObject()
{
	TWeakObjectPtr< UiJsonObject > tempJsonObject = NewObject<UiJsonObject>();
	if (JsonObject.IsValid())
	{
		(*tempJsonObject.Get()).JsonObject = (*JsonObject.Get()).JsonObject;
		(*tempJsonObject.Get()).NewJsonString = (*JsonObject.Get()).NewJsonString;
	}
		
	return tempJsonObject.Get();
}


#undef LOCTEXT_NAMESPACE