// Little Mario Game: Course Project. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class LittleMarioEditorTarget : TargetRules
{
	public LittleMarioEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "LittleMario" } );
	}
}
