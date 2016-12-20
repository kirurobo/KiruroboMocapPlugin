// Copyright (c) 2015 Kirurobo

#pragma once

#include "MocapBones.h"
#include "ReceivedSkeleton.generated.h"


/**
 * UDP receiver base class
 */
UCLASS(ClassGroup = MocapPlugin)
class UReceivedSkeleton : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	virtual ~UReceivedSkeleton();

protected:

	int8 BONE_NUMBER = 0;

	virtual void Initialize();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		int32 UserId = -1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mocap")
		TArray<FQuat> LastBoneRotations;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mocap")
		TArray<FQuat> BoneRotations;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mocap")
		FVector RootPosition = FVector(0, 0, 0);
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		FVector PositionOffset = FVector(0, 0, 0);
};


