// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Async_Shooter : ModuleRules
{
	public Async_Shooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Steam", "lib", "steam_api64.lib"));
	}
}
