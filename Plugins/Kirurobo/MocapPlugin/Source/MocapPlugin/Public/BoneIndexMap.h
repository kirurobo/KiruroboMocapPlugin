// Copyright (c) 2015-2016 Kirurobo

#pragma once

#include "MocapBones.h"
#include "BoneIndexMap.generated.h"

/**
 * スケルタルメッシュのボーン番号とモーキャプのボーン対応を保持する構造体
 */
USTRUCT()
struct FBoneIndexMap
{
	GENERATED_USTRUCT_BODY()
	
public:
	/**
	* 対象スケルタルメッシュのボーン番号
	*/
	int MeshBoneIndex;

	/**
	* 本プラグインでの統一ボーン
	*/
	TEnumAsByte<EMocapBones::Type> MocapBone;
	
	
	/**
	* デフォルト値のコンストラクタ
	*/
	FBoneIndexMap();
	
	/**
	* 値を指定したコンストラクタ
	*/
	FBoneIndexMap(const int meshBoneIndex, const EMocapBones::Type mocapBone);
};
