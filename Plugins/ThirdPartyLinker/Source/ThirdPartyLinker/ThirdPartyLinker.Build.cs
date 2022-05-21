// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;


public class ThirdPartyLinker : ModuleRules
{
	private string ModulePath
	{
		get { return ModuleDirectory; }
	}

	private string ThirdPartyPath
	{
		get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
	}

	public ThirdPartyLinker(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicDelayLoadDLLs.Add(Path.Combine(ThirdPartyPath, "Mediapipe", "Binaries", "Win64", "ump_shared.dll"));
			PublicDelayLoadDLLs.Add(Path.Combine(ThirdPartyPath, "Mediapipe", "Binaries", "Win64", "opencv_world3410.dll"));
			RuntimeDependencies.Add((Path.Combine(ThirdPartyPath, "Mediapipe", "Binaries", "Win64", "ump_shared.dll")));
			RuntimeDependencies.Add((Path.Combine(ThirdPartyPath, "Mediapipe", "Binaries", "Win64", "opencv_world3410.dll")));
			// RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(ThirdPartyPath, "Mediapipe", "Binaries", "Win64", "ump_shared.dll")));
			// RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(ThirdPartyPath, "Mediapipe", "Binaries", "Win64", "opencv_world3410.dll")));
		}
		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			/*			//mediapipe ump_shared.so
						AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(ModuleDirectory, "Mediapipe_APL.xml")));
						PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "Mediapipe", "Binaries", "Android", "ump_shared.so"));*/

			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(ModuleDirectory, "Test_APL.xml"));
			/*
			//test.so
			string so_path = Path.Combine(ThirdPartyPath, "Test_so");
			string so_file_path = Path.Combine(so_path, "libtest.so");
			//System.Console.WriteLine("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\nso_file_path=");
			//System.Console.WriteLine(so_file_path);
			PublicIncludePaths.Add(so_path + "/includes");
			RuntimeDependencies.Add(so_file_path);

			PublicRuntimeLibraryPaths.Add(so_path);
			PublicLibraryPaths.Add(so_path);
			PublicAdditionalLibraries.Add(so_path + "/libopencv_java3.so");
			PublicAdditionalLibraries.Add(so_path + "/libhello-greet.so");
			PublicAdditionalLibraries.Add(so_path + "/libmediapipe_jni.so");
			// PublicAdditionalLibraries.Add(so_path + "/libtest.so");
			*/
		}

		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"ThirdPartyLinkerLibrary",
				"Projects"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Launch",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
