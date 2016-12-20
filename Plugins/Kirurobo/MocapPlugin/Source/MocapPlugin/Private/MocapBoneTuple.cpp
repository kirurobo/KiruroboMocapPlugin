// Copyright (c) 2015 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "MocapBoneTuple.h"

FMocapBoneTuple::FMocapBoneTuple()
{
	Bone = FName("");
	MocapBone = EMocapBones::Root;
}


FMocapBoneTuple::FMocapBoneTuple(const FName name, const EMocapBones::Type mocapBone)
{
	Bone = name;
	MocapBone = mocapBone;
}
