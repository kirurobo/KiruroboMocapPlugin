// Copyright (c) 2015 Kirurobo

#pragma once

#include "Runtime/Launch/Resources/Version.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimNodeSpaceConversions.h"
#if (ENGINE_MAJOR_VERSION >= 4) && (ENGINE_MINOR_VERSION >= 11)
#include "Animation/AnimInstanceProxy.h"
#endif

#include "MocapBones.h"
#include "MocapBoneTuple.h"
#include "MocapReceiver.h"
#include "MocapPluginGameInstance.h"
#include "MocapPluginAnimInstance.generated.h"

#if (ENGINE_MAJOR_VERSION >= 4) && (ENGINE_MINOR_VERSION >= 11)
class UMocapPluginAnimInstance;
struct FMocapPluginAnimInstanceProxy : public FAnimInstanceProxy
{
	UMocapPluginAnimInstance* MocapPluginAnimInstance;

	FMocapPluginAnimInstanceProxy() : FAnimInstanceProxy(), MocapPluginAnimInstance(nullptr)
	{}

	FMocapPluginAnimInstanceProxy(UAnimInstance* animInstance) : FAnimInstanceProxy(animInstance), MocapPluginAnimInstance(nullptr)
	{}

	virtual bool Evaluate(FPoseContext& Output) override;
};
#endif

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

#if (ENGINE_MAJOR_VERSION >= 4) && (ENGINE_MINOR_VERSION >= 11)
	/**
	* アニメーション評価タイミングで呼ばれます
	*/
	bool EvaluateMocap(struct FPoseContext& Output);

	FMocapPluginAnimInstanceProxy Proxy;

	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override
	{
		return&Proxy;
	}

	virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* proxy) override
	{}

	friend struct FMocapPluginAnimInstanceProxy;
#else
	/**
	* アニメーション評価タイミングで呼ばれます
	*/
	virtual bool NativeEvaluateAnimation(struct FPoseContext& Output) override;
#endif

	/**
	* 統一ボーン配列の要素数
	*/
	uint8 BoneCount = 0;

	///** 親ボーンの姿勢を再帰的に計算 */
	//FQuat UMocapPluginAnimInstance::RecursiveParentRotation(FA2CSPose pose, TArray<FQuat> rotations, int32 boneIndex);


	/**
	* 各ボーンの姿勢が入る配列
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Mocap")
		TArray<FQuat> BoneRotations;

	/**
	* MocapPluginGameInstanceが見つかればここに入る
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Mocap")
		UMocapPluginGameInstance *MocapPluginGameInstance;

	/**
	* MocapReceiverが見つかればここに入る
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Mocap")
		UMocapReceiver *MocapReceiver;

public:
	/**
	* モーションキャプチャからのデータのうち、このAnimInstanceで対象とするユーザーID。
	* 複数人分を同時に送信しているならば指定する。
	* -1にするとユーザーIDで区別せず、受信したものをすべて利用する。
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		int32 UserId = -1;

	/**
	* 位置を移動させるかどうか
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		bool UseRootPosition = true;

	/**
	* モデルの位置を取得する
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		bool IsMirrored = false;

	/**
	* モデルとMocapPlugin間のボーン名対応を指定します
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mocap")
		TArray<FMocapBoneTuple> BoneMap;

	///**
	//* 自動的にT-ポーズに調整するか
	//*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
	//	bool EnforceTPose = true;

	/**
	* モデルの位置を取得する
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mocap")
		FVector RootPosition = FVector(0, 0, 0);


	/**
	* モーキャプで受信されたボーンの姿勢を取得します。
	* 各姿勢は親ボーンに対する相対姿勢です。
	*/
	UFUNCTION(BlueprintCallable, Category = "Mocap")
		FRotator GetBoneRotator(EMocapBones::Type bone) const;

	/**
	* 基準座標を取得します。
	* モーキャプからの値に最初の位置を基準としたオフセットを加えたものです。
	*/
	UFUNCTION(BlueprintCallable, Category = "Mocap")
		FVector GetRootPosition() const;

	///**
	//* オフセットを取得します。
	//*/
	//UFUNCTION(BlueprintCallable, Category = "Mocap")
	//	FVector GetPositionOffset() const;


	/**
	* 本プラグインのボーン名を配列のインデックス番号にキャストします
	*/
	UFUNCTION(BlueprintCallable, Category = "Mocap")
		static uint8 GetBoneIndex(EMocapBones::Type bone);

	//UFUNCTION(BlueprintCallable, Category = "Mocap")
	//	FComponentSpacePoseLink ApplyMocapPose(FComponentSpacePoseLink pose) const;

};
