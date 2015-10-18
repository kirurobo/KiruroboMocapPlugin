// Copyright (c) 2015 Kirurobo

#pragma once

#include "MocapBones.h"
#include "MocapPose.generated.h"


/**
 * あるユーザーIDのある瞬間の姿勢を保持するコンテナ
 */
UCLASS(ClassGroup = MocapPlugin)
class UMocapPose : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	virtual ~UMocapPose();

protected:
	virtual void Initialize();

public:
	/* 統一ボーン数 */
	int8 boneTotalNumber;

	/** 基準座標とモーションデータ間の変位。初受信時に記録される */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		FVector PositionOffset;

	/** モーキャプでの座標 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mocap")
		FVector OriginalRootPosition;

	/** 各ボーンの姿勢 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mocap")
		TArray<FQuat> BoneRotations;

	/** このデータのユーザーID */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mocap")
		int32 UserId = 0;

	/** 座標を取得。モーキャプの値にオフセットを加えたものが得られます。 */
	UFUNCTION(BlueprintCallable, Category = "Mocap")
		FVector GetRootPosition();

	/** 複製を作成する */
	UMocapPose* Clone();

	/** 指定のインスタンスに内容を複製する */
	void CopyTo(UMocapPose* pose);
};


