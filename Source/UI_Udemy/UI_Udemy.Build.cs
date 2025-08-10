// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UI_Udemy : ModuleRules
{
	public UI_Udemy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG", 
			"GameplayTags", 
			"UMG", 
			"DeveloperSettings"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"UI_Udemy",
			"UI_Udemy/Variant_Platforming",
			"UI_Udemy/Variant_Combat",
			"UI_Udemy/Variant_Combat/AI",
			"UI_Udemy/Variant_SideScrolling",
			"UI_Udemy/Variant_SideScrolling/Gameplay",
			"UI_Udemy/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
