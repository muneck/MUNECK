/*
*  Copyright (c) 2016-2018 YeHaike(841660657@qq.com).
*  All rights reserved.
*  @ Date : 2018/05/03
*
*/

#include "iJsonObject.h"

#define LOCTEXT_NAMESPACE "iJsonObject"

UiJsonObject::UiJsonObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

}


bool UiJsonObject::TryGetNumberField(const FString& FieldName, float& OutNumber)
{
	if (!JsonObject.IsValid())
		return false;
	double tempDouble;
	bool returnBool = (*JsonObject.Get()).TryGetNumberField(FieldName, tempDouble);
	OutNumber = tempDouble;
	return returnBool;
}

bool UiJsonObject::TryGetStringField(const FString& FieldName, FString& OutString)
{
	if (!JsonObject.IsValid())
		return false;
	return (*JsonObject.Get()).TryGetStringField(FieldName, OutString);
}

bool UiJsonObject::TryGetBoolField(const FString& FieldName, bool& OutBool)
{
	if (!JsonObject.IsValid())
		return false;
	return (*JsonObject.Get()).TryGetBoolField(FieldName, OutBool);
}

bool UiJsonObject::TryGetObjectField(const FString& FieldName, UiJsonObject*& OutiJsonObject)
{
	if (!JsonObject.IsValid())
		return false;
	const TSharedPtr<FJsonObject>* OutObject;
	bool resultBool = (*JsonObject.Get()).TryGetObjectField(FieldName, OutObject);
	if (!resultBool)
		return false;
	TWeakObjectPtr< UiJsonObject > tempJsonObject = NewObject<UiJsonObject>();
	(*tempJsonObject.Get()).JsonObject = *OutObject;
	OutiJsonObject = tempJsonObject.Get();
	return resultBool;
}

bool UiJsonObject::TryGetStringArrayField(const FString& FieldName, TArray<FString>& OutArray)
{
	if (!JsonObject.IsValid())
		return false;
	return (*JsonObject.Get()).TryGetStringArrayField(FieldName, OutArray);
}

bool UiJsonObject::TryGetNumberArrayField(const FString& FieldName, TArray<float>& OutArray)
{
	if (!JsonObject.IsValid())
		return false;

	TSharedPtr<FJsonValue> Field = (*JsonObject.Get()).TryGetField(FieldName);

	if (!Field.IsValid())
	{
		return false;
	}

	const TArray< TSharedPtr<FJsonValue> > *Array;

	if (!Field->TryGetArray(Array))
	{
		return false;
	}

	for (int Idx = 0; Idx < Array->Num(); Idx++)
	{
		double Element;

		if (!(*Array)[Idx]->TryGetNumber(Element))
		{
			return false;
		}

		float tempFloat = Element;
		OutArray.Add(Element);
	}

	return true;
}


bool UiJsonObject::TryGetJsonObjectArrayField(const FString& FieldName, TArray<UiJsonObject*>& OutArray)
{
	if (!JsonObject.IsValid())
		return false;

	TSharedPtr<FJsonValue> Field = (*JsonObject.Get()).TryGetField(FieldName);

	if (!Field.IsValid())
	{
		return false;
	}

	const TArray< TSharedPtr<FJsonValue> > *Array;

	if (!Field->TryGetArray(Array))
	{
		return false;
	}

	for (int Idx = 0; Idx < Array->Num(); Idx++)
	{
		const TSharedPtr<FJsonObject>* Element;
		FString JsonString;
		if (!(*Array)[Idx]->TryGetObject(Element))
		{
			return false;
		}
		

		TWeakObjectPtr< UiJsonObject > tempJsonObject = NewObject<UiJsonObject>();
		(*tempJsonObject.Get()).JsonObject = *Element;

		(*Array)[Idx]->TryGetString(JsonString);

		(*tempJsonObject.Get()).NewJsonString = JsonString;

		OutArray.Add(tempJsonObject.Get());
	}

	return true;
}


bool UiJsonObject::ConstructJsonObjectFromSelfJsonString(FText& OutFailReason)
{
	// Deserialize a Json object from the string
	return ConstructJsonObjectFromJsonString(NewJsonString, OutFailReason);
}


bool UiJsonObject::ConstructJsonObjectFromJsonString(const FString& JsonString, FText& OutFailReason)
{
	TSharedPtr< FJsonObject > JsonObjectTemp;
	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(JsonString);
	if (!FJsonSerializer::Deserialize(Reader, JsonObjectTemp) || !JsonObjectTemp.IsValid())
	{
		OutFailReason = FText::Format(LOCTEXT("ConstructJsonObjectFromJsonString", "Construct JsonObject From JsonString. {0}"), FText::FromString(Reader->GetErrorMessage()));
		return false;
	}

	this->JsonObject = JsonObjectTemp;
	this->NewJsonString = JsonString;

	return true;
}

#undef LOCTEXT_NAMESPACE