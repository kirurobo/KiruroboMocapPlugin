// Copyright (c) 2015 Kirurobo

#pragma once

#include "Animation/AnimInstance.h"
#include "Animation/AnimNodeSpaceConversions.h"
#include "MocapBones.h"
#include "MocapReceiver.h"
#include "MocapPluginGameInstance.h"
#include "MocapPluginAnimInstance.generated.h"

/**
 * MocapPluginGameInstanceへの接続を目的としたAnimInstance拡張
 */
UCLASS(ClassGroup = MocapPlugin)
class UMocapPluginAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMocapPluginAnimInstance(const FObjectInitializer& ObjectInitializer);

protected:
	/**
	* AnimInstanceが初期化される際に呼ばれます。
	* エディタでは開いた際、プレイを開始した際など、何度も呼ばれます
	*/
	void NativeInitializeAnimation() override;

	/**
	* アニメーションの更新タイミングで繰り返し呼ばれます
	*/
	void NativeUpdateAnimation(float deltaTime) override;

	/**
	* アニメーション評価タイミングで呼ばれます
	*/
	virtual bool NativeEvaluateAnimation(FPoseContext& Output) override;

	/**
	* 統一ボーン配列の要素数
	*/
	uint8 BoneCount = 0;

	///** 親ボーンの姿勢を再帰的に計算 */
	//FQuat UMocapPluginAnimInstance::RecursiveParentRotation(FA2CSPose pose, TArray<FQuat> rotations, int32 boneIndex);


	/**
	* 各ボーンの姿勢が入る配列
	*/
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mocap")
		TArray<FQuat> BoneRotations;

	/**
	* MocapPluginGameInstanceが見つかればここに入る
	*/
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mocap")
		UMocapPluginGameInstance *MocapPluginGameInstance;

	/**
	* MocapReceiverが見つかればここに入る
	*/
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mocap")
		UMocapReceiver *MocapReceiver;

public:
	/**
	* モーションキャプチャからのデータのうち、このAnimInstanceで対象とするユーザーID。
	* -1にするとユーザーIDで区別しない。
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		int32 UserId = -1;

	/**
	* 位置を移動させるかどうか
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		bool UseRootPosition = true;

	/**
	* 動かすボーン名を順に指定する
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		TArray<FName> BoneNames;

	/**
	* 割り当てるボーンを順に指定する
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		TArray<TEnumAsByte<EMocapBones::Type>> MocapBones;

	/**
	* モデルの位置を取得する
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mocap")
		FVector RootPosition = FVector(0, 0, 0);


	UFUNCTION(BlueprintCallable, Category = "Mocap")
		FRotator GetBoneRotator(EMocapBones::Type bone) const;

	UFUNCTION(BlueprintCallable, Category = "Mocap")
		static uint8 GetBoneIndex(EMocapBones::Type bone);

	UFUNCTION(BlueprintCallable, Category = "Mocap")
		FComponentSpacePoseLink ApplyMocapPose(FComponentSpacePoseLink pose) const;
};
