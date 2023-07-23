// Little Mario Game: Course Project. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class LittleMarioTarget : TargetRules
{
	public LittleMarioTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "LittleMario" } );
	}
}
