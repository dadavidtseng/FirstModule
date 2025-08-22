//----------------------------------------------------------------------------------------------------
// Manual.Build.cs
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------

using UnrealBuildTool;

//----------------------------------------------------------------------------------------------------
public class Manual : ModuleRules
{
	public Manual(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange([
			"Core",
			"Auto"
		]);

		PrivateDependencyModuleNames.AddRange([
			"CoreUObject",
			"Engine"
		]);
	}
}