//----------------------------------------------------------------------------------------------------
// FirstModule.Build.cs
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------

using UnrealBuildTool;

//----------------------------------------------------------------------------------------------------
public class FirstModule : ModuleRules
{
	public FirstModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(["Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput"]);

		PrivateDependencyModuleNames.AddRange([]);
	}
}