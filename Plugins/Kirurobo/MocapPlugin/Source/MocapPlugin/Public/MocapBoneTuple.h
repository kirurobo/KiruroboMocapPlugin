// Copyright (c) 2015 Kirurobo

#pragma once

#include "MocapBones.h"
#include "MocapBoneTuple.generated.h"

/**
* スケルタルメッシュとモーキャプのボーン対応を定義します
*/
USTRUCT()
struct FMocapBoneTuple
{
	GENERATED_USTRUCT_BODY()

public:
	/**
	* 対象スケルタルメッシュのボーン名
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
	FName Bone;

	/**
	* 本プラグインでの統一ボーン名
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
	TEnumAsByte<EMocapBones::Type> MocapBone;


	FMocapBoneTuple();

	FMocapBoneTuple(const FName name, const EMocapBones::Type mocapBone);
};
