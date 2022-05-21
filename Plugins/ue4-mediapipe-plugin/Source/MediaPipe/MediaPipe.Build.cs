using UnrealBuildTool;
using System.IO;

public class MediaPipe : ModuleRules
{
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }

    public MediaPipe(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.NoPCHs; // UseExplicitOrSharedPCHs;
        bUseUnity = false;
        bUseRTTI = true;

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicDelayLoadDLLs.Add(Path.Combine(ThirdPartyPath, "Mediapipe", "Binaries", "Win64", "ump_shared.dll"));
            PublicDelayLoadDLLs.Add(Path.Combine(ThirdPartyPath, "Mediapipe", "Binaries", "Win64", "opencv_world3410.dll"));
            RuntimeDependencies.Add((Path.Combine(ThirdPartyPath, "Mediapipe", "Binaries", "Win64", "ump_shared.dll")));
            RuntimeDependencies.Add((Path.Combine(ThirdPartyPath, "Mediapipe", "Binaries", "Win64", "opencv_world3410.dll")));
        }
/*        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(ModuleDirectory, "MP_Android_APL.xml"));
        }*/

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "Slate",
                "SlateCore",
                "Launch",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Projects",
            }
        );

        string BinArch = Target.Platform.ToString();
        string LibExt = "";
        string DllExt = ".so";

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            LibExt = ".lib";
            DllExt = ".dll";

            string BinaryOutputDir = "$(BinaryOutputDir)";
            string ThirdPartyDir = Path.Combine(ModuleDirectory, "..", "..", "ThirdParty");//the ThirdParty of the plugin

            // protobuf deps
            //note:protobuf is implicit linked,
            //meaning it has a .lib and do not need to use things like DllLoader(just include .h and use the functions),
            //for now we need to add the additional .lib and add runtime deps on the corresponding dll

            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                PublicDefinitions.Add("PROTOBUF_USE_DLLS=1");
            }

            PublicIncludePaths.Add(Path.Combine(ThirdPartyDir, "protobuf", "Include")); //tell where the protobuf.h file is so we can include it using name instead of path.
            PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyDir, "protobuf", "Lib", BinArch, "libprotobuf" + LibExt));

            string ProtobufBinDir = Path.Combine(ThirdPartyDir, "protobuf", "Binaries", BinArch);
            AddDep("libprotobuf", DllExt, ProtobufBinDir, BinaryOutputDir);

            // mediapipe deps
            //note:protobuf is explicit linked,
            //meaning it has no .lib and need to use things like DllLoader,
            //for now we only need to add runtime deps on the dll

            string MPBinDir = Path.Combine(ThirdPartyDir, "mediapipe", "Binaries", BinArch);
            string MPDataDir = Path.Combine(ThirdPartyDir, "mediapipe", "Data");// contains all the .tflites and .pbtxt file

            AddDep("opencv_world3410", DllExt, MPBinDir, BinaryOutputDir);
            AddDep("ump_shared", DllExt, MPBinDir, BinaryOutputDir);

            if (Target.Type != TargetType.Editor)// for packaging for shipping/debuggame/development, add runtime deps on all the .tflites and .pbtxt file
                AddDepFolder(MPDataDir, BinaryOutputDir);
        }
        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(ModuleDirectory, "MP_Android_APL.xml")));

            string ThirdPartyDir = Path.Combine(ModuleDirectory, "..", "..", "ThirdParty");
            PublicIncludePaths.Add(Path.Combine(ThirdPartyDir, "protobuf", "Include"));
        }

        
    }

    private void AddDep(string FileName, string Ext, string SourceDir, string TargetDir)//filename and ext descride the file, SDir:where to find, TD: where to place and add deps
    {
        RuntimeDependencies.Add(Path.Combine(TargetDir, FileName + Ext), Path.Combine(SourceDir, FileName + Ext));//.Add(path,[SourcePath])
    }

    private void AddDepFolder(string SourceDir, string TargetDir)
    {
        foreach (string filePath in Directory.GetFiles(SourceDir, "*.*", SearchOption.AllDirectories))
        {
            string dst = filePath.Replace(SourceDir, TargetDir);
            RuntimeDependencies.Add(dst, filePath);
        }
    }
}
