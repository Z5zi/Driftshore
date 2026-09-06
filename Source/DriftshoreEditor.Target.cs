// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

using UnrealBuildTool;
using System.Collections.Generic;

public class DriftshoreEditorTarget : TargetRules
{
	public DriftshoreEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("Driftshore");
		ExtraModuleNames.Add("DriftshoreEditor");
	}
}
