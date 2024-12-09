using UnrealBuildTool;
using System.IO;

public class LocalTesting : ModuleRules
{
    public LocalTesting(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG" });

        // Add OpenCV include and library paths
        string OpenCVPath = Path.Combine(ModuleDirectory, "../../opencv/build");

        // Include path
        PublicIncludePaths.Add(Path.Combine(OpenCVPath, "include"));

        // Library path
        PublicAdditionalLibraries.Add(Path.Combine(OpenCVPath, "x64/vc16/lib/opencv_world4100.lib"));
    }
}
