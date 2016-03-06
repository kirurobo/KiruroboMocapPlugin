// Copyright (c) 2015-2016 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "BoneIndexMap.h"

FBoneIndexMap::FBoneIndexMap()
{
	MeshBoneIndex = 0;
	MocapBone = EMocapBones::Root;
}


FBoneIndexMap::FBoneIndexMap(const int meshBoneIndex, const EMocapBones::Type mocapBone)
{
	MeshBoneIndex = meshBoneIndex;
	MocapBone = mocapBone;
}
