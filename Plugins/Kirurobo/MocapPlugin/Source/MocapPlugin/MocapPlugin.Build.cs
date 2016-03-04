// Copyright (c) 2015-2016 Kirurobo

namespace UnrealBuildTool.Rules
{
	public class MocapPlugin : ModuleRules
	{
		public MocapPlugin(TargetInfo Target)
		{
			PublicIncludePaths.AddRange(
				new string[] {
					"MocapPlugin/Public",
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"MocapPlugin/Private",
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine",
					"Networking",
					"Sockets",
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					// ... add private dependencies that you statically link with here ...
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
				);
		}
	}
}