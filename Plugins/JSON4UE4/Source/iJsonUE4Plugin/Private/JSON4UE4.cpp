/*
*  Copyright (c) 2016-2018 YeHaike(841660657@qq.com).
*  All rights reserved.
*  @ Date : 2018/05/03
*
*/

#include "JSON4UE4.h"

#define LOCTEXT_NAMESPACE "FJSON4UE4Module"

void FJSON4UE4Module::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FJSON4UE4Module::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FJSON4UE4Module, JSON4UE4)