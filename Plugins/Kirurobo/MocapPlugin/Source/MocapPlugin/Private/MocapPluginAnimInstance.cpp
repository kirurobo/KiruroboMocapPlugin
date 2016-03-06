// Copyright (c) 2015-2016 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "MocapPluginAnimInstance.h"
#include "MocapBoneMap.h"
#include "Runtime/Launch/Resources/Version.h"


/**
* 初期化
*/
void UMocapPluginAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	this->MocapPluginGameInstance = NULL;

	/* 統一ボーン数を取得 */
	UEnum* pMocapBones = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMocapBones"), true);
	this->BoneCount = pMocapBones->NumEnums();

	/* 位置の初期値 */
	this->RootPosition = FVector(0, 0, 0);

	UGameInstance* gameInstance;
	UWorld* world = this->GetWorld();

	if (world) {
		gameInstance = world->GetGameInstance();
		if (gameInstance) {
			this->MocapPluginGameInstance = Cast<UMocapPluginGameInstance>(gameInstance);

			if (this->MocapPluginGameInstance) {
				this->MocapReceiver = this->MocapPluginGameInstance->MocapReceiver;
			}
		}
	}

	//USkeletalMeshComponent* meshComponent = GetOwningComponent();

	InitializeBoneMap();
}

/**
* ボーン名でのDataTableから番号での対応付けを生成
*/
bool UMocapPluginAnimInstance::InitializeBoneMap()
{
	USkeletalMeshComponent* meshComponent = GetOwningComponent();
	if (!meshComponent) return false;

	if (!this->BoneTable) return false;
	UDataTable* table = this->BoneTable;
	if (!table) return false;

	UE_LOG(LogInit, Log, TEXT("Init bone map for mesh : %s"), *(meshComponent->GetName()));

	/* 各ボーンに受信された変形を反映 */
	TArray<FName> mapArray = table->GetRowNames();
	this->boneIndices.Empty(mapArray.Num());
	for (int i = 0; i < mapArray.Num(); i++) {
		FMocapBoneMap* map = table->FindRow<FMocapBoneMap>(mapArray[i], TEXT("MocapBoneMap"));
		FName boneName = map->MeshBone;
		uint8 mocapBoneIndex = map->MocapBone;

		FBoneIndexType boneIndex = meshComponent->GetBoneIndex(boneName);
		if (boneIndex < 0 || boneIndex > 0x7FFF) continue;

		FBoneIndexMap boneIndexMap = FBoneIndexMap();
		boneIndexMap.MeshBoneIndex = boneIndex;
		boneIndexMap.MocapBone = map->MocapBone;

		this->boneIndices.Add(boneIndexMap);
	}
	return true;
}

/**
* 更新ごとに呼ばれる
*/
void UMocapPluginAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);
}

/**
* 骨を指定してFRotatorを取得
*/
FRotator UMocapPluginAnimInstance::GetBoneRotator(EMocapBones::Type boneIndex) const
{
	if (this->BoneRotations.Num() > boneIndex) {
		return FRotator(this->BoneRotations[boneIndex]);
	}
	else {
		return FRotator(0, 0, 0);
	}
}

/**
* ルート座標を取得
*/
FVector UMocapPluginAnimInstance::GetRootPosition() const
{
	return this->RootPosition;
}

///**
//* 座標オフセット値を取得
//*/
//FVector UMocapPluginAnimInstance::GetPositionOffset() const
//{
//	return this->MocapReceiver->GetMocapPose(this->UserId)->PositionOffset;
//}

/**
* 骨列挙体を指定して番号を取得
*/
uint8 UMocapPluginAnimInstance::GetBoneIndex(EMocapBones::Type boneIndex)
{
	return (uint8) boneIndex;
}

///**
//* アニムグラフで利用できるか検証中。未実装。
//*/
//FComponentSpacePoseLink UMocapPluginAnimInstance::ApplyMocapPose(FComponentSpacePoseLink pose) const
//{
//	if (this->BoneRotations.Num() < this->BoneCount) return pose;
//	
//	USkeletalMeshComponent* meshComponent = GetOwningComponent();
//	if (!meshComponent) return pose;
//
//	return pose;
//}


/**
* 姿勢の評価時に毎回実行される
*
* @return trueだとノードグラフは評価されない
*/
bool UMocapPluginAnimInstance::NativeEvaluateAnimation(FPoseContext& Output)
{
	/* モーションの自動適用オフか、MocapReceiver がなければ何もしない */
	if (!this->AutoApply) return false;

	if (this->MocapReceiver) {
		UMocapPose* mocapPose = this->MocapReceiver->GetMocapPose(this->UserId);
		this->BoneRotations = mocapPose->BoneRotations;
		this->RootPosition = mocapPose->GetRootPosition();
	} else {
		return false;
	}

	if (this->BoneRotations.Num() < this->BoneCount) return false;

	USkeletalMeshComponent* meshComponent = GetOwningComponent();
	if (!meshComponent) return false;

	if (RootNode != NULL) {
		RootNode->Evaluate(Output);
	}
	else {
		Output.ResetToRefPose();
	}

#if (ENGINE_MAJOR_VERSION >= 4) && (ENGINE_MINOR_VERSION >= 9)
	/* UE 4.9 以降の場合。 FPoseContext の中身が変わり、そのまま使えなくなった。 */

	/* Rootからの親ボーン姿勢を計算。子より必ず親の番号が小さくなければならない。 */
	const static int maxBones = 255;
	FQuat parentRotations[maxBones];
	for (int i = 0; i < Output.Pose.GetNumBones() && i < maxBones; i++) {
		FCompactPoseBoneIndex index(i);
		FQuat rotation = Output.Pose[index].GetRotation();
		FCompactPoseBoneIndex parentPoseBoneIndex = Output.Pose.GetParentBoneIndex(index);
		int parentIndex = parentPoseBoneIndex.GetInt();
		if (parentIndex >= 0 && parentIndex < maxBones) {
			rotation = parentRotations[parentIndex] * rotation;
		}
		parentRotations[i] = rotation;
	}

	/* 各ボーンに受信された変形を反映 */
	for (int i = 0; i < this->boneIndices.Num(); i++) {
		uint8 mocapBoneIndex = this->boneIndices[i].MocapBone;
		FBoneIndexType boneIndex = this->boneIndices[i].MeshBoneIndex;
		FCompactPoseBoneIndex index(boneIndex);
		FTransform transform = Output.Pose[index];
		FQuat rotation = this->BoneRotations[mocapBoneIndex];

		//UE_LOG(LogTemp, Log, TEXT("Root Rot.: %d %d"), boneIndex, rotation.X);

		FCompactPoseBoneIndex parentBoneIndex = Output.Pose.GetParentBoneIndex(index);
		if (parentBoneIndex >= 0) {
			FQuat parentRotation = parentRotations[parentBoneIndex.GetInt()];
			rotation = parentRotation.Inverse() * rotation * parentRotation * transform.GetRotation();
		}
		else {
			rotation = rotation * transform.GetRotation();
		}
		transform.SetRotation(rotation);
		Output.Pose[index].SetRotation(rotation);
	}

	/* ルートの移動を反映 */
	if (this->UseRootPosition && (Output.Pose.GetNumBones() > 0)) {
		FCompactPoseBoneIndex index(0);
		Output.Pose[index].SetTranslation(this->RootPosition);

		//UE_LOG(LogTemp, Log, TEXT("Root position: %d %f %f %f"), index.GetInt(), this->RootPosition.X, this->RootPosition.Y, this->RootPosition.Z);
	}
#else
	/* UE 4.8 以前の場合 */

	FA2CSPose pose;
	pose.AllocateLocalPoses(RequiredBones, Output.Pose);

	/* Rootからの親ボーン姿勢を計算。子より必ず親の番号が小さくなければならない。 */
	const static int maxBones = 255;
	FQuat parentRotations[maxBones];
	for (int i = 0; i < pose.Bones.Num() && i < maxBones; i++) {
		FQuat rotation = pose.Bones[i].GetRotation();
		int32 parentBoneIndex = pose.GetParentBoneIndex(i);
		if (parentBoneIndex >= 0 && parentBoneIndex < maxBones) {
			rotation = parentRotations[parentBoneIndex] * rotation;
		}
		parentRotations[i] = rotation;
	}

	/* 各ボーンに受信された変形を反映 */
	for (int i = 0; i < this->boneIndices.Num(); i++) {
		uint8 mocapBoneIndex = this->boneIndices[i].MocapBone;
		int32 boneIndex = this->boneIndices[i].MeshBoneIndex;
		FTransform transform = pose.Bones[boneIndex];
		FQuat rotation = this->BoneRotations[mocapBoneIndex];

		int32 parentBoneIndex = pose.GetParentBoneIndex(boneIndex);
		if (parentBoneIndex >= 0) {
			FQuat parentRotation = parentRotations[parentBoneIndex];
			rotation = parentRotation.Inverse() * rotation * parentRotation * transform.GetRotation();
		}
		else {
			rotation = rotation * transform.GetRotation();
		}
		transform.SetRotation(rotation);
		pose.Bones[boneIndex] = transform;
	}

	/* ルートの移動を反映 */
	if (this->UseRootPosition && (Output.Pose.Bones.Num() > 0)) {
		pose.Bones[0].SetTranslation(this->RootPosition);

		//UE_LOG(LogTemp, Log, TEXT("Root position: %f %f %f"), this->RootPosition.X, this->RootPosition.Y, this->RootPosition.Z);
	}

	pose.ConvertToLocalPoses(Output.Pose);

#endif

	return true;
}
