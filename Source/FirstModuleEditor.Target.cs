//----------------------------------------------------------------------------------------------------
// FirstModuleEditor.Target.cs
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------

using UnrealBuildTool;

//----------------------------------------------------------------------------------------------------
public class FirstModuleEditorTarget : TargetRules
{
	public FirstModuleEditorTarget(TargetInfo Target) : base(Target)
	{
		Type                 = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion  = EngineIncludeOrderVersion.Unreal5_6;
		ExtraModuleNames.Add("FirstModule");
		RegisterModulesCreatedByRider();
	}

	private void RegisterModulesCreatedByRider()
	{
		ExtraModuleNames.AddRange(["Auto", "Manual", "Migrate"]);
	}
}