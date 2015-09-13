// Copyright (c) 2015 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "MocapPluginAnimInstance.h"

/**
* コンストラクタ
*/
UMocapPluginAnimInstance::UMocapPluginAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/* グレーマンの骨格に従ってデフォルト値を設定 */
	this->BoneNames.Add(FName("root"));
	this->BoneNames.Add(FName("pelvis"));
	this->BoneNames.Add(FName("spine_01"));
	this->BoneNames.Add(FName("spine_01"));
	this->BoneNames.Add(FName("spine_02"));
	this->BoneNames.Add(FName("spine_03"));
	this->BoneNames.Add(FName("clavicle_l"));
	this->BoneNames.Add(FName("upperarm_l"));
	this->BoneNames.Add(FName("lowerarm_l"));
	this->BoneNames.Add(FName("hand_l"));
	this->BoneNames.Add(FName("clavicle_r"));
	this->BoneNames.Add(FName("upperarm_r"));
	this->BoneNames.Add(FName("lowerarm_r"));
	this->BoneNames.Add(FName("hand_r"));
	this->BoneNames.Add(FName("neck_01"));
	this->BoneNames.Add(FName("head"));
	this->BoneNames.Add(FName("thigh_l"));
	this->BoneNames.Add(FName("calf_l"));
	this->BoneNames.Add(FName("foot_l"));
	this->BoneNames.Add(FName("ball_l"));
	this->BoneNames.Add(FName("thigh_r"));
	this->BoneNames.Add(FName("calf_r"));
	this->BoneNames.Add(FName("foot_r"));
	this->BoneNames.Add(FName("ball_r"));
	this->BoneNames.Add(FName("lowerarm_twist_l"));
	this->BoneNames.Add(FName("upperarm_twist_l"));
	this->BoneNames.Add(FName("thumb_01_l"));
	this->BoneNames.Add(FName("thumb_02_l"));
	this->BoneNames.Add(FName("thumb_03_l"));
	this->BoneNames.Add(FName("index_01_l"));
	this->BoneNames.Add(FName("index_01_l"));
	this->BoneNames.Add(FName("index_02_l"));
	this->BoneNames.Add(FName("index_03_l"));
	this->BoneNames.Add(FName("middle_01_l"));
	this->BoneNames.Add(FName("middle_01_l"));
	this->BoneNames.Add(FName("middle_02_l"));
	this->BoneNames.Add(FName("middle_03_l"));
	this->BoneNames.Add(FName("ring_01_l"));
	this->BoneNames.Add(FName("ring_01_l"));
	this->BoneNames.Add(FName("ring_02_l"));
	this->BoneNames.Add(FName("ring_03_l"));
	this->BoneNames.Add(FName("pinky_01_l"));
	this->BoneNames.Add(FName("pinky_01_l"));
	this->BoneNames.Add(FName("pinky_02_l"));
	this->BoneNames.Add(FName("pinky_03_l"));
	this->BoneNames.Add(FName("lowerarm_twist_r"));
	this->BoneNames.Add(FName("upperarm_twist_r"));
	this->BoneNames.Add(FName("thumb_01_r"));
	this->BoneNames.Add(FName("thumb_02_r"));
	this->BoneNames.Add(FName("thumb_03_r"));
	this->BoneNames.Add(FName("index_01_r"));
	this->BoneNames.Add(FName("index_01_r"));
	this->BoneNames.Add(FName("index_02_r"));
	this->BoneNames.Add(FName("index_03_r"));
	this->BoneNames.Add(FName("middle_01_r"));
	this->BoneNames.Add(FName("middle_01_r"));
	this->BoneNames.Add(FName("middle_02_r"));
	this->BoneNames.Add(FName("middle_03_r"));
	this->BoneNames.Add(FName("ring_01_r"));
	this->BoneNames.Add(FName("ring_01_r"));
	this->BoneNames.Add(FName("ring_02_r"));
	this->BoneNames.Add(FName("ring_03_r"));
	this->BoneNames.Add(FName("pinky_01_r"));
	this->BoneNames.Add(FName("pinky_01_r"));
	this->BoneNames.Add(FName("pinky_02_r"));
	this->BoneNames.Add(FName("pinky_03_r"));
	this->BoneNames.Add(FName("thigh_twist_l"));
	this->BoneNames.Add(FName("calf_twist_l"));
	this->BoneNames.Add(FName("thigh_twist_r"));
	this->BoneNames.Add(FName("calf_twist_r"));

	/*  統一ボーンのデフォルト値を設定 */
	this->MocapBones.Add(EMocapBones::Root);
	this->MocapBones.Add(EMocapBones::Pelvis);
	this->MocapBones.Add(EMocapBones::Spine01);
	this->MocapBones.Add(EMocapBones::Spine01L3);
	this->MocapBones.Add(EMocapBones::Spine02);
	this->MocapBones.Add(EMocapBones::Spine03);
	this->MocapBones.Add(EMocapBones::LeftClavicle);
	this->MocapBones.Add(EMocapBones::LeftUpperArm);
	this->MocapBones.Add(EMocapBones::LeftLowerArm);
	this->MocapBones.Add(EMocapBones::LeftHand);
	this->MocapBones.Add(EMocapBones::RightClavicle);
	this->MocapBones.Add(EMocapBones::RightUpperArm);
	this->MocapBones.Add(EMocapBones::RightLowerArm);
	this->MocapBones.Add(EMocapBones::RightHand);
	this->MocapBones.Add(EMocapBones::Neck);
	this->MocapBones.Add(EMocapBones::Head);
	this->MocapBones.Add(EMocapBones::LeftThigh);
	this->MocapBones.Add(EMocapBones::LeftCalf);
	this->MocapBones.Add(EMocapBones::LeftFoot);
	this->MocapBones.Add(EMocapBones::LeftBall);
	this->MocapBones.Add(EMocapBones::RightThigh);
	this->MocapBones.Add(EMocapBones::RightCalf);
	this->MocapBones.Add(EMocapBones::RightFoot);
	this->MocapBones.Add(EMocapBones::RightBall);
	this->MocapBones.Add(EMocapBones::LeftLowerArmTwist);
	this->MocapBones.Add(EMocapBones::LeftUpperArmTwist);
	this->MocapBones.Add(EMocapBones::LeftThumb01);
	this->MocapBones.Add(EMocapBones::LeftThumb02);
	this->MocapBones.Add(EMocapBones::LeftThumb03);
	this->MocapBones.Add(EMocapBones::LeftInHandIndex);
	this->MocapBones.Add(EMocapBones::LeftIndex01);
	this->MocapBones.Add(EMocapBones::LeftIndex02);
	this->MocapBones.Add(EMocapBones::LeftIndex03);
	this->MocapBones.Add(EMocapBones::LeftInHandMiddle);
	this->MocapBones.Add(EMocapBones::LeftMiddle01);
	this->MocapBones.Add(EMocapBones::LeftMiddle02);
	this->MocapBones.Add(EMocapBones::LeftMiddle03);
	this->MocapBones.Add(EMocapBones::LeftInHandRing);
	this->MocapBones.Add(EMocapBones::LeftRing01);
	this->MocapBones.Add(EMocapBones::LeftRing02);
	this->MocapBones.Add(EMocapBones::LeftRing03);
	this->MocapBones.Add(EMocapBones::LeftInHandPinky);
	this->MocapBones.Add(EMocapBones::LeftPinky01);
	this->MocapBones.Add(EMocapBones::LeftPinky02);
	this->MocapBones.Add(EMocapBones::LeftPinky03);
	this->MocapBones.Add(EMocapBones::RightLowerArmTwist);
	this->MocapBones.Add(EMocapBones::RightUpperArmTwist);
	this->MocapBones.Add(EMocapBones::RightThumb01);
	this->MocapBones.Add(EMocapBones::RightThumb02);
	this->MocapBones.Add(EMocapBones::RightThumb03);
	this->MocapBones.Add(EMocapBones::RightInHandIndex);
	this->MocapBones.Add(EMocapBones::RightIndex01);
	this->MocapBones.Add(EMocapBones::RightIndex02);
	this->MocapBones.Add(EMocapBones::RightIndex03);
	this->MocapBones.Add(EMocapBones::RightInHandMiddle);
	this->MocapBones.Add(EMocapBones::RightMiddle01);
	this->MocapBones.Add(EMocapBones::RightMiddle02);
	this->MocapBones.Add(EMocapBones::RightMiddle03);
	this->MocapBones.Add(EMocapBones::RightInHandRing);
	this->MocapBones.Add(EMocapBones::RightRing01);
	this->MocapBones.Add(EMocapBones::RightRing02);
	this->MocapBones.Add(EMocapBones::RightRing03);
	this->MocapBones.Add(EMocapBones::RightInHandPinky);
	this->MocapBones.Add(EMocapBones::RightPinky01);
	this->MocapBones.Add(EMocapBones::RightPinky02);
	this->MocapBones.Add(EMocapBones::RightPinky03);
	this->MocapBones.Add(EMocapBones::LeftThighTwist);
	this->MocapBones.Add(EMocapBones::LeftCalfTwist);
	this->MocapBones.Add(EMocapBones::RightThighTwist);
	this->MocapBones.Add(EMocapBones::RightCalfTwist);
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
* 骨列挙体を指定して番号を取得
*/
uint8 UMocapPluginAnimInstance::GetBoneIndex(EMocapBones::Type boneIndex)
{
	return (uint8) boneIndex;
}

/**
* アニムグラフで利用できるか検証中。未実装。
*/
FComponentSpacePoseLink UMocapPluginAnimInstance::ApplyMocapPose(FComponentSpacePoseLink pose) const
{
	if (this->BoneRotations.Num() < this->BoneCount) return pose;
	
	USkeletalMeshComponent* meshComponent = GetOwningComponent();
	if (!meshComponent) return pose;

	return pose;
}


/**
* 姿勢の評価時に毎回実行される
*
* @return trueだとノードグラフは評価されない
*/
bool UMocapPluginAnimInstance::NativeEvaluateAnimation(FPoseContext& Output)
{
	if (this->MocapReceiver) {
		this->BoneRotations = this->MocapReceiver->BoneRotations;
		this->RootPosition = this->MocapReceiver->RootPosition;
	} else {
		return false;
	}

	if (this->BoneRotations.Num() < this->BoneCount) return false;

	if (RootNode != NULL) {
		RootNode->Evaluate(Output);
	}
	else {
		Output.ResetToRefPose();
	}

	USkeletalMeshComponent* meshComponent = GetOwningComponent();
	if (!meshComponent) return false;

	FA2CSPose pose;
	pose.AllocateLocalPoses(RequiredBones, Output.Pose);

	/* Rootからの親ボーン姿勢を計算。子より必ず親の番号が小さくなければならない。 */
	TArray<FQuat> parentRotations;
	parentRotations.Reserve(pose.Bones.Num());
	for (int i = 0; i < pose.Bones.Num(); i++) {
		FQuat rotation = pose.Bones[i].GetRotation();
		int32 parentBoneIndex = pose.GetParentBoneIndex(i);
		if (parentBoneIndex >= 0 && parentBoneIndex < parentRotations.Num()) {
			rotation = parentRotations[parentBoneIndex] * rotation;
		}
		parentRotations.Add(rotation);
	}

	/* 各ボーンに受信された変形を反映 */
	for (int i = 0; i < this->BoneNames.Num(); i++) {
		if (this->MocapBones.Num() <= i) break;

		FName boneName = this->BoneNames[i];
		uint8 mocapBoneIndex = this->MocapBones[i];

		int32 boneIndex = meshComponent->GetBoneIndex(boneName);
		if (boneIndex < 0) continue;

		FTransform transform = pose.Bones[boneIndex];
		FQuat rotation = this->BoneRotations[mocapBoneIndex];

		//UE_LOG(LogTemp, Log, TEXT("Root Rot.: %d %d"), boneIndex, rotation.X);

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

	return true;
}
