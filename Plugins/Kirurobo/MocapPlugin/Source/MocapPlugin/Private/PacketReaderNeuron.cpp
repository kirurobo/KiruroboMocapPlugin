// Copyright (c) 2015 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "PacketReaderNeuron.h"

const uint8 UPacketReaderNeuron::BoneCount = 59;

/**
* パケットでの登場順とボーンの対応付け
*/
const uint8 UPacketReaderNeuron::BoneIndices [] = {
	(uint8) EMocapNeuronBones::Hips,
	(uint8) EMocapNeuronBones::RightUpLeg,
	(uint8) EMocapNeuronBones::RightLeg,
	(uint8) EMocapNeuronBones::RightFoot,
	(uint8) EMocapNeuronBones::LeftUpLeg,
	(uint8) EMocapNeuronBones::LeftLeg,
	(uint8) EMocapNeuronBones::LeftFoot,
	(uint8) EMocapNeuronBones::Spine,
	(uint8) EMocapNeuronBones::Spine1,
	(uint8) EMocapNeuronBones::Spine2,
	(uint8) EMocapNeuronBones::Spine3,
	(uint8) EMocapNeuronBones::Neck,
	(uint8) EMocapNeuronBones::Head,
	(uint8) EMocapNeuronBones::RightShoulder,
	(uint8) EMocapNeuronBones::RightArm,
	(uint8) EMocapNeuronBones::RightForeArm,
	(uint8) EMocapNeuronBones::RightHand,
	(uint8) EMocapNeuronBones::RightHandThumb1,
	(uint8) EMocapNeuronBones::RightHandThumb2,
	(uint8) EMocapNeuronBones::RightHandThumb3,
	(uint8) EMocapNeuronBones::RightInHandIndex,
	(uint8) EMocapNeuronBones::RightHandIndex1,
	(uint8) EMocapNeuronBones::RightHandIndex2,
	(uint8) EMocapNeuronBones::RightHandIndex3,
	(uint8) EMocapNeuronBones::RightInHandMiddle,
	(uint8) EMocapNeuronBones::RightHandMiddle1,
	(uint8) EMocapNeuronBones::RightHandMiddle2,
	(uint8) EMocapNeuronBones::RightHandMiddle3,
	(uint8) EMocapNeuronBones::RightInHandRing,
	(uint8) EMocapNeuronBones::RightHandRing1,
	(uint8) EMocapNeuronBones::RightHandRing2,
	(uint8) EMocapNeuronBones::RightHandRing3,
	(uint8) EMocapNeuronBones::RightInHandPinky,
	(uint8) EMocapNeuronBones::RightHandPinky1,
	(uint8) EMocapNeuronBones::RightHandPinky2,
	(uint8) EMocapNeuronBones::RightHandPinky3,
	(uint8) EMocapNeuronBones::LeftShoulder,
	(uint8) EMocapNeuronBones::LeftArm,
	(uint8) EMocapNeuronBones::LeftForeArm,
	(uint8) EMocapNeuronBones::LeftHand,
	(uint8) EMocapNeuronBones::LeftHandThumb1,
	(uint8) EMocapNeuronBones::LeftHandThumb2,
	(uint8) EMocapNeuronBones::LeftHandThumb3,
	(uint8) EMocapNeuronBones::LeftInHandIndex,
	(uint8) EMocapNeuronBones::LeftHandIndex1,
	(uint8) EMocapNeuronBones::LeftHandIndex2,
	(uint8) EMocapNeuronBones::LeftHandIndex3,
	(uint8) EMocapNeuronBones::LeftInHandMiddle,
	(uint8) EMocapNeuronBones::LeftHandMiddle1,
	(uint8) EMocapNeuronBones::LeftHandMiddle2,
	(uint8) EMocapNeuronBones::LeftHandMiddle3,
	(uint8) EMocapNeuronBones::LeftInHandRing,
	(uint8) EMocapNeuronBones::LeftHandRing1,
	(uint8) EMocapNeuronBones::LeftHandRing2,
	(uint8) EMocapNeuronBones::LeftHandRing3,
	(uint8) EMocapNeuronBones::LeftInHandPinky,
	(uint8) EMocapNeuronBones::LeftHandPinky1,
	(uint8) EMocapNeuronBones::LeftHandPinky2,
	(uint8) EMocapNeuronBones::LeftHandPinky3,
};

/**
* パケットでの登場順と親ボーンの対応付け
*/
const uint8 UPacketReaderNeuron::ParentBones [] = {
	(uint8) EMocapNeuronBones::None,
	(uint8) EMocapNeuronBones::Hips,
	(uint8) EMocapNeuronBones::RightUpLeg,
	(uint8) EMocapNeuronBones::RightLeg,
	(uint8) EMocapNeuronBones::Hips,
	(uint8) EMocapNeuronBones::LeftUpLeg,
	(uint8) EMocapNeuronBones::LeftLeg,
	(uint8) EMocapNeuronBones::Hips,
	(uint8) EMocapNeuronBones::Spine,
	(uint8) EMocapNeuronBones::Spine1,
	(uint8) EMocapNeuronBones::Spine2,
	(uint8) EMocapNeuronBones::Spine3,
	(uint8) EMocapNeuronBones::Neck,
	(uint8) EMocapNeuronBones::Spine3,
	(uint8) EMocapNeuronBones::RightShoulder,
	(uint8) EMocapNeuronBones::RightArm,
	(uint8) EMocapNeuronBones::RightForeArm,
	(uint8) EMocapNeuronBones::RightHand,
	(uint8) EMocapNeuronBones::RightHandThumb1,
	(uint8) EMocapNeuronBones::RightHandThumb2,
	(uint8) EMocapNeuronBones::RightHand,
	(uint8) EMocapNeuronBones::RightInHandIndex,
	(uint8) EMocapNeuronBones::RightHandIndex1,
	(uint8) EMocapNeuronBones::RightHandIndex2,
	(uint8) EMocapNeuronBones::RightHand,
	(uint8) EMocapNeuronBones::RightInHandMiddle,
	(uint8) EMocapNeuronBones::RightHandMiddle1,
	(uint8) EMocapNeuronBones::RightHandMiddle2,
	(uint8) EMocapNeuronBones::RightHand,
	(uint8) EMocapNeuronBones::RightInHandRing,
	(uint8) EMocapNeuronBones::RightHandRing1,
	(uint8) EMocapNeuronBones::RightHandRing2,
	(uint8) EMocapNeuronBones::RightHand,
	(uint8) EMocapNeuronBones::RightInHandPinky,
	(uint8) EMocapNeuronBones::RightHandPinky1,
	(uint8) EMocapNeuronBones::RightHandPinky2,
	(uint8) EMocapNeuronBones::Spine3,
	(uint8) EMocapNeuronBones::LeftShoulder,
	(uint8) EMocapNeuronBones::LeftArm,
	(uint8) EMocapNeuronBones::LeftForeArm,
	(uint8) EMocapNeuronBones::LeftHand,
	(uint8) EMocapNeuronBones::LeftHandThumb1,
	(uint8) EMocapNeuronBones::LeftHandThumb2,
	(uint8) EMocapNeuronBones::LeftHand,
	(uint8) EMocapNeuronBones::LeftInHandIndex,
	(uint8) EMocapNeuronBones::LeftHandIndex1,
	(uint8) EMocapNeuronBones::LeftHandIndex2,
	(uint8) EMocapNeuronBones::LeftHand,
	(uint8) EMocapNeuronBones::LeftInHandMiddle,
	(uint8) EMocapNeuronBones::LeftHandMiddle1,
	(uint8) EMocapNeuronBones::LeftHandMiddle2,
	(uint8) EMocapNeuronBones::LeftHand,
	(uint8) EMocapNeuronBones::LeftInHandRing,
	(uint8) EMocapNeuronBones::LeftHandRing1,
	(uint8) EMocapNeuronBones::LeftHandRing2,
	(uint8) EMocapNeuronBones::LeftHand,
	(uint8) EMocapNeuronBones::LeftInHandPinky,
	(uint8) EMocapNeuronBones::LeftHandPinky1,
	(uint8) EMocapNeuronBones::LeftHandPinky2,
};


UPacketReaderNeuron::UPacketReaderNeuron() : UPacketReader()
{
	Initialize();
}

//UPacketReaderNeuron::UPacketReaderNeuron(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//	Initialize();
//}

// Sets default values
void UPacketReaderNeuron::Initialize()
{
	this->SampleCount = 0;

	/*  初期化 */
	this->RootPosition = FVector::ZeroVector;
	this->PositionOffset = FVector::ZeroVector;
	this->IsFirstReceive = true;

	/*  値を保持する配列を準備 */
	BoneRotations.Reserve(BoneNumber);
	lastRotations.Reserve(BoneNumber);
	for (int i = 0; i < BoneNumber; i++) {
		BoneRotations.Add(FQuat(0, 0, 0, 1));
		lastRotations.Add(FQuat(0, 0, 0, 1));
	}
}

/*  一つ分の受信データを解析し、AXIS Neuron の BVH データならば格納 */
bool UPacketReaderNeuron::Read(const FArrayReaderPtr& data)
{
	if (!CheckHeader(data)) return false;

	const uint8* raw = data->GetData();
	int index = 64;
	
	/*  Refecence ありの場合、float16 × 6 がヘッダー後に存在するのでスキップ */
	if (this->hasReference) index += 24;

	/*  最初はルート位置が届く */
	FVector position = GetPosition(raw, index);
	index += 12;

	/*  初回受信ならオフセットを記憶 */
	if (this->IsFirstReceive) {
		this->PositionOffset = -position;
		this->IsFirstReceive = false;
	}
	this->RootPosition = position + this->PositionOffset;

	/*  各関節の角度 */
	for (int i = 0; i < BoneCount; i++) {
		ProcessSegment(raw, i, index);
		index += (this->hasDisplacement ? 24 : 12);
	}

	return true;
}

void UPacketReaderNeuron::ProcessSegment(const uint8* data, const int32 segmentNo, const int32 index)
{
	int32 num = segmentNo;
	uint8 boneIndex = this->BoneIndices[num];

	FQuat quat = GetQuaternion(data, index);

	this->BoneRotations[boneIndex] = quat;
	this->lastRotations[boneIndex] = quat;
}

/*  扱えるMVNのデータかヘッダを確認 */
bool UPacketReaderNeuron::CheckHeader(const FArrayReaderPtr& data)
{
	/*  ヘッダ部の長さ未満なら不正として終了 */
	if (data->Num() < 63) return false;

	const uint8* raw = data->GetData();
	int32 index = 0;

	/*  先頭の文字列を確認 */
	if (GetUInt16(raw, 0) != 0xDDFF) return false;

	/*  データカウント */
	index = 6;
	uint32 dataCount = GetUInt32(raw, index);
	index += 4;

	/*  データ数と受信された長さが一致しなければ不正として終了 */
	if (data->Num() != (dataCount * 4 + 64)) return false;

	/*  変位もデータに含まれるか */
	this->hasDisplacement = (GetUInt32(raw, index) != 0);
	index += 4;

	/*  リファレンスが含まれるか */
	this->hasReference = (GetUInt32(raw, index) != 0);
	index += 4;

	/*  アバターID */
	int32 userId = GetUInt32(raw, index);
	index += 4;

	/*  ヘッダーの終了を確認 */
	if (GetUInt16(raw, 62) != 0xEEFF) return false;

	return true;
}

/* 座標をUEの座標系で返す */
FVector UPacketReaderNeuron::GetPosition(const uint8* data, const int32 index)
{
	return FVector(
		GetFloat(data, index),
		GetFloat(data, index + 8),
		GetFloat(data, index + 4)
		);
}

/**
* 座標をUEの座標系で返す。AXIS Neuron では XZY の順としておくこと！
*/
FQuat UPacketReaderNeuron::GetQuaternion(const uint8* data, const int32 index)
{
	FVector euler = FVector();

	/*  for XZY */
	euler.X = GetFloat(data, index);
	euler.Y = GetFloat(data, index + 4);
	euler.Z = -GetFloat(data, index + 8);

	FQuat quat = FQuat::MakeFromEuler(euler);

	return quat;
}
