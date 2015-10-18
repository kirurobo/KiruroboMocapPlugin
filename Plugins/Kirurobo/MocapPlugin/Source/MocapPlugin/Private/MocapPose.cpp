// Copyright (c) 2015 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "MocapPose.h"


UMocapPose::UMocapPose( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	Initialize();
}

UMocapPose::~UMocapPose()
{
}

// Sets default values
void UMocapPose::Initialize()
{
	UEnum* pBones = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMocapBones"), true);
	this->boneTotalNumber = pBones->NumEnums();

	/* ルート座標を初期化 */
	this->OriginalRootPosition = FVector(0, 0, 0);

	/* 座標オフセットを初期化 */
	this->PositionOffset = FVector(0, 0, 0);

	/*  各ボーンの姿勢を保持する配列を準備 */
	BoneRotations.Reserve(this->boneTotalNumber);
	for (int i = 0; i < this->boneTotalNumber; i++) {
		BoneRotations.Add(FQuat(0, 0, 0, 1));
	}
}

/* 自分自身の複製作成して返す */
FVector UMocapPose::GetRootPosition()
{
	return this->OriginalRootPosition + this->PositionOffset;
}

/* 自分自身の複製作成して返す */
UMocapPose* UMocapPose::Clone()
{
	UMocapPose* pose;
	pose = NewObject<UMocapPose>();
	pose->OriginalRootPosition = this->OriginalRootPosition;
	pose->PositionOffset= this->PositionOffset;

	for (int i = 0; i < this->boneTotalNumber; i++)
	{
		pose->BoneRotations[i] = this->BoneRotations[i];
	}

	return pose;
}

/* 自分自身の複製作成して返す */
void UMocapPose::CopyTo(UMocapPose* pose)
{
	pose->OriginalRootPosition = this->OriginalRootPosition;
	pose->PositionOffset = this->PositionOffset;
	
	for (int i = 0; i < this->boneTotalNumber; i++)
	{
		pose->BoneRotations[i] = this->BoneRotations[i];
	}
}