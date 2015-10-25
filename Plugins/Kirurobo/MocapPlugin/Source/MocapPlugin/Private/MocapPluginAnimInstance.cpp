// Copyright (c) 2015 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "MocapPluginAnimInstance.h"
#include "Runtime/Launch/Resources/Version.h"

/**
* コンストラクタ
*/
UMocapPluginAnimInstance::UMocapPluginAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/* グレーマンの骨格に従ってデフォルト値を設定 */
	this->BoneMap.Add(FMocapBoneTuple(FName("root"), EMocapBones::Root));
	this->BoneMap.Add(FMocapBoneTuple(FName("pelvis"), EMocapBones::Pelvis));
	this->BoneMap.Add(FMocapBoneTuple(FName("spine_01"), EMocapBones::Spine01));
	this->BoneMap.Add(FMocapBoneTuple(FName("spine_01"), EMocapBones::Spine01L3));
	this->BoneMap.Add(FMocapBoneTuple(FName("spine_02"), EMocapBones::Spine02));
	this->BoneMap.Add(FMocapBoneTuple(FName("spine_03"), EMocapBones::Spine03));
	this->BoneMap.Add(FMocapBoneTuple(FName("clavicle_l"), EMocapBones::LeftClavicle));
	this->BoneMap.Add(FMocapBoneTuple(FName("upperarm_l"), EMocapBones::LeftUpperArm));
	this->BoneMap.Add(FMocapBoneTuple(FName("lowerarm_l"), EMocapBones::LeftLowerArm));
	this->BoneMap.Add(FMocapBoneTuple(FName("hand_l"), EMocapBones::LeftHand));
	this->BoneMap.Add(FMocapBoneTuple(FName("clavicle_r"), EMocapBones::RightClavicle));
	this->BoneMap.Add(FMocapBoneTuple(FName("upperarm_r"), EMocapBones::RightUpperArm));
	this->BoneMap.Add(FMocapBoneTuple(FName("lowerarm_r"), EMocapBones::RightLowerArm));
	this->BoneMap.Add(FMocapBoneTuple(FName("hand_r"), EMocapBones::RightHand));
	this->BoneMap.Add(FMocapBoneTuple(FName("neck_01"), EMocapBones::Neck));
	this->BoneMap.Add(FMocapBoneTuple(FName("head"), EMocapBones::Head));
	this->BoneMap.Add(FMocapBoneTuple(FName("thigh_l"), EMocapBones::LeftThigh));
	this->BoneMap.Add(FMocapBoneTuple(FName("calf_l"), EMocapBones::LeftCalf));
	this->BoneMap.Add(FMocapBoneTuple(FName("foot_l"), EMocapBones::LeftFoot));
	this->BoneMap.Add(FMocapBoneTuple(FName("ball_l"), EMocapBones::LeftBall));
	this->BoneMap.Add(FMocapBoneTuple(FName("thigh_r"), EMocapBones::RightThigh));
	this->BoneMap.Add(FMocapBoneTuple(FName("calf_r"), EMocapBones::RightCalf));
	this->BoneMap.Add(FMocapBoneTuple(FName("foot_r"), EMocapBones::RightFoot));
	this->BoneMap.Add(FMocapBoneTuple(FName("ball_r"), EMocapBones::RightBall));
	this->BoneMap.Add(FMocapBoneTuple(FName("lowerarm_twist_l"), EMocapBones::LeftLowerArmTwist));
	this->BoneMap.Add(FMocapBoneTuple(FName("upperarm_twist_l"), EMocapBones::LeftUpperArmTwist));
	this->BoneMap.Add(FMocapBoneTuple(FName("thumb_01_l"), EMocapBones::LeftThumb01));
	this->BoneMap.Add(FMocapBoneTuple(FName("thumb_02_l"), EMocapBones::LeftThumb02));
	this->BoneMap.Add(FMocapBoneTuple(FName("thumb_03_l"), EMocapBones::LeftThumb03));
	this->BoneMap.Add(FMocapBoneTuple(FName("index_01_l"), EMocapBones::LeftInHandIndex));
	this->BoneMap.Add(FMocapBoneTuple(FName("index_01_l"), EMocapBones::LeftIndex01));
	this->BoneMap.Add(FMocapBoneTuple(FName("index_02_l"), EMocapBones::LeftIndex02));
	this->BoneMap.Add(FMocapBoneTuple(FName("index_03_l"), EMocapBones::LeftIndex03));
	this->BoneMap.Add(FMocapBoneTuple(FName("middle_01_l"), EMocapBones::LeftInHandMiddle));
	this->BoneMap.Add(FMocapBoneTuple(FName("middle_01_l"), EMocapBones::LeftMiddle01));
	this->BoneMap.Add(FMocapBoneTuple(FName("middle_02_l"), EMocapBones::LeftMiddle02));
	this->BoneMap.Add(FMocapBoneTuple(FName("middle_03_l"), EMocapBones::LeftMiddle03));
	this->BoneMap.Add(FMocapBoneTuple(FName("ring_01_l"), EMocapBones::LeftInHandRing));
	this->BoneMap.Add(FMocapBoneTuple(FName("ring_01_l"), EMocapBones::LeftRing01));
	this->BoneMap.Add(FMocapBoneTuple(FName("ring_02_l"), EMocapBones::LeftRing02));
	this->BoneMap.Add(FMocapBoneTuple(FName("ring_03_l"), EMocapBones::LeftRing03));
	this->BoneMap.Add(FMocapBoneTuple(FName("pinky_01_l"), EMocapBones::LeftInHandPinky));
	this->BoneMap.Add(FMocapBoneTuple(FName("pinky_01_l"), EMocapBones::LeftPinky01));
	this->BoneMap.Add(FMocapBoneTuple(FName("pinky_02_l"), EMocapBones::LeftPinky02));
	this->BoneMap.Add(FMocapBoneTuple(FName("pinky_03_l"), EMocapBones::LeftPinky03));
	this->BoneMap.Add(FMocapBoneTuple(FName("lowerarm_twist_r"), EMocapBones::RightLowerArmTwist));
	this->BoneMap.Add(FMocapBoneTuple(FName("upperarm_twist_r"), EMocapBones::RightUpperArmTwist));
	this->BoneMap.Add(FMocapBoneTuple(FName("thumb_01_r"), EMocapBones::RightThumb01));
	this->BoneMap.Add(FMocapBoneTuple(FName("thumb_02_r"), EMocapBones::RightThumb02));
	this->BoneMap.Add(FMocapBoneTuple(FName("thumb_03_r"), EMocapBones::RightThumb03));
	this->BoneMap.Add(FMocapBoneTuple(FName("index_01_r"), EMocapBones::RightInHandIndex));
	this->BoneMap.Add(FMocapBoneTuple(FName("index_01_r"), EMocapBones::RightIndex01));
	this->BoneMap.Add(FMocapBoneTuple(FName("index_02_r"), EMocapBones::RightIndex02));
	this->BoneMap.Add(FMocapBoneTuple(FName("index_03_r"), EMocapBones::RightIndex03));
	this->BoneMap.Add(FMocapBoneTuple(FName("middle_01_r"), EMocapBones::RightInHandMiddle));
	this->BoneMap.Add(FMocapBoneTuple(FName("middle_01_r"), EMocapBones::RightMiddle01));
	this->BoneMap.Add(FMocapBoneTuple(FName("middle_02_r"), EMocapBones::RightMiddle02));
	this->BoneMap.Add(FMocapBoneTuple(FName("middle_03_r"), EMocapBones::RightMiddle03));
	this->BoneMap.Add(FMocapBoneTuple(FName("ring_01_r"), EMocapBones::RightInHandRing));
	this->BoneMap.Add(FMocapBoneTuple(FName("ring_01_r"), EMocapBones::RightRing01));
	this->BoneMap.Add(FMocapBoneTuple(FName("ring_02_r"), EMocapBones::RightRing02));
	this->BoneMap.Add(FMocapBoneTuple(FName("ring_03_r"), EMocapBones::RightRing03));
	this->BoneMap.Add(FMocapBoneTuple(FName("pinky_01_r"), EMocapBones::RightInHandPinky));
	this->BoneMap.Add(FMocapBoneTuple(FName("pinky_01_r"), EMocapBones::RightPinky01));
	this->BoneMap.Add(FMocapBoneTuple(FName("pinky_02_r"), EMocapBones::RightPinky02));
	this->BoneMap.Add(FMocapBoneTuple(FName("pinky_03_r"), EMocapBones::RightPinky03));
	this->BoneMap.Add(FMocapBoneTuple(FName("thigh_twist_l"), EMocapBones::LeftThighTwist));
	this->BoneMap.Add(FMocapBoneTuple(FName("calf_twist_l"), EMocapBones::LeftCalfTwist));
	this->BoneMap.Add(FMocapBoneTuple(FName("thigh_twist_r"), EMocapBones::RightThighTwist));
	this->BoneMap.Add(FMocapBoneTuple(FName("calf_twist_r"), EMocapBones::RightCalfTwist));
}

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
	if (this->MocapReceiver) {
		UMocapPose* pose = this->MocapReceiver->GetMocapPose(this->UserId);
		this->BoneRotations = pose->BoneRotations;
		this->RootPosition = pose->GetRootPosition();
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
	for (int i = 0; i < this->BoneMap.Num(); i++) {
		FName boneName = this->BoneMap[i].Bone;
		uint8 mocapBoneIndex = this->BoneMap[i].MocapBone;

		FBoneIndexType boneIndex = meshComponent->GetBoneIndex(boneName);
		if (boneIndex < 0 || boneIndex > 0x7FFF) continue;

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
	for (int i = 0; i < this->BoneMap.Num(); i++) {
		FName boneName = this->BoneMap[i].Bone;
		uint8 mocapBoneIndex = this->BoneMap[i].MocapBone;

		int32 boneIndex = meshComponent->GetBoneIndex(boneName);
		if (boneIndex < 0) continue;

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
