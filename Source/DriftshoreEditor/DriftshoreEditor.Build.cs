// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

using UnrealBuildTool;

public class DriftshoreEditor : ModuleRules
{
	public DriftshoreEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"UnrealEd",
			"Driftshore"
		});
	}
}
