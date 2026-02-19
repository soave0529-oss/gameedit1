using UnrealBuildTool;

public class JoseonGTA : ModuleRules
{
    public JoseonGTA(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "UMG",
            "AIModule",
            "GameplayTasks",
            "NavigationSystem",
            "Json",
            "JsonUtilities",
            "DeveloperSettings",
            "NetCore"
        });
    }
}
