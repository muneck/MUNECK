// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CFL_FolderManager.generated.h"

/**
 * 
 */
UCLASS()
class MUNECK_V2_API UCFL_FolderManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
		UFUNCTION(BlueprintCallable, Category = "Find")
		static TArray<FString> FindFilesRecursive(FString Path, FString Filter, bool InFiles, bool InDirectory);

};
