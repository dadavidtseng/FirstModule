//----------------------------------------------------------------------------------------------------
// Auto.Build.cs
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------

using UnrealBuildTool;

//----------------------------------------------------------------------------------------------------
public class Auto : ModuleRules
{
    public Auto(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            [
                "Core"
            ]
        );

        PrivateDependencyModuleNames.AddRange(
            [
                "CoreUObject",
                "Engine"
            ]
        );
    }
}