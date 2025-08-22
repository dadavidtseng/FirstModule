using UnrealBuildTool;

public class Manual : ModuleRules
{
    public Manual(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange([
            "Core"
        ]);

        PrivateDependencyModuleNames.AddRange([
            "CoreUObject",
            "Engine"
        ]);
    }
}