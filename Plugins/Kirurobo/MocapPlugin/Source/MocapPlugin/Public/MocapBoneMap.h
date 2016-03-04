// Copyright (c) 2015-2016 Kirurobo

#pragma once

#include "MocapBones.h"
#include "MocapBoneMap.generated.h"

/**
 * スケルタルメッシュのボーンとモーキャプのボーン対応を保持する構造体
 */
USTRUCT(Blueprintable)
struct FMocapBoneMap : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
public:
	/**
	* 対象スケルタルメッシュのボーン名
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mocap")
		FName MeshBone;

	/**
	* 本プラグインでの統一ボーン名
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		TEnumAsByte<EMocapBones::Type> MocapBone;
};
