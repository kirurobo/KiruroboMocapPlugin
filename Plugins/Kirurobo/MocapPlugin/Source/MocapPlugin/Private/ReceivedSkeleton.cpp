// Copyright (c) 2015 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "ReceivedSkeleton.h"


UReceivedSkeleton::UReceivedSkeleton( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	Initialize();
}

UReceivedSkeleton::~UReceivedSkeleton()
{
}

// Sets default values
void UReceivedSkeleton::Initialize()
{
	UEnum* pBones = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMocapBones"), true);
	BONE_NUMBER = pBones->NumEnums();

	/*  値を保持する配列を準備 */
	BoneRotations.Reserve(BONE_NUMBER);
	for (int i = 0; i < BONE_NUMBER; i++) {
		BoneRotations.Add(FQuat(0, 0, 0, 1));
	}
}
