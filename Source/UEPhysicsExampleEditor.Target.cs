// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class UEPhysicsExampleEditorTarget : TargetRules
{
	public UEPhysicsExampleEditorTarget(TargetInfo Target) : base(Target)
    {
		Type = TargetType.Editor;

        ExtraModuleNames.AddRange(new string[] { "UEPhysicsExample" });
    }
}
