// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;

public class MUNECK_v2 : ModuleRules
{
	string OPENCV_VERSION = "3410";
	private string ThirdPartyPath
	{
		get
		{
			return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/"));
		}
	}
	public bool LoadOpenCV(ReadOnlyTargetRules Target)
	{
		// Start OpenCV linking
		bool isLibrarySupported = false;// Create OpenCV Path
		string OpenCVPath = Path.Combine(ThirdPartyPath, "OpenCV");// Get Library Path
		string LibPath = "";
		bool isdebug = Target.Configuration == UnrealTargetConfiguration.Debug;
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			LibPath = Path.Combine(OpenCVPath, "Libraries", "Win64");
			isLibrarySupported = true;
		}
		else
		{
			string Err = string.Format("{0} dedicated server is made to depend on {1}. We want to avoid this, please correct module dependencies.", Target.Platform.ToString(), this.ToString());
			System.Console.WriteLine(Err);
		}
		if (isLibrarySupported)
		{
			//Add Include path
			PublicIncludePaths.AddRange(new string[] { Path.Combine(OpenCVPath, "Includes") });
			//Add Static Libraries
			PublicAdditionalLibraries.Add(Path.Combine(LibPath, "opencv_world" + OPENCV_VERSION + ".lib"));
			//Add Dynamic Libraries
			PublicDelayLoadDLLs.Add("opencv_world" + OPENCV_VERSION + ".dll");
			PublicDelayLoadDLLs.Add("opencv_videoio_ffmpeg" + OPENCV_VERSION + "_64.dll");
		}
		PublicDefinitions.Add(string.Format("WITH_OPENCV_BINDING={0}", isLibrarySupported ? 1 : 0));
		return isLibrarySupported;
	}
	public MUNECK_v2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Third party plugin
		PublicDependencyModuleNames.AddRange(new string[] { "MediaPipe" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
		LoadOpenCV(Target);
		PublicDependencyModuleNames.AddRange(new string[] { "RHI", "RenderCore", "Media", "MediaAssets" });
	}
	
}
