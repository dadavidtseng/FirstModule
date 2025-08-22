//----------------------------------------------------------------------------------------------------
// FirstModule.Target.cs
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------

using UnrealBuildTool;

//----------------------------------------------------------------------------------------------------
public class FirstModuleTarget : TargetRules
{
	public FirstModuleTarget(TargetInfo Target) : base(Target)
	{
		Type                 = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion  = EngineIncludeOrderVersion.Unreal5_6;
		ExtraModuleNames.Add("FirstModule");
		RegisterModulesCreatedByRider();
	}

	private void RegisterModulesCreatedByRider()
	{
		ExtraModuleNames.AddRange(["Auto", "Manual"]);
	}
}