// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FmediapipeModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// UFUNCTION(blueprint)
	// void DetectFace();

private:
	/** Handle to the test dll we will load */
	void*	ExampleLibraryHandle;
};
