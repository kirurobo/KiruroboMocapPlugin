// Copyright (c) 2015-2016 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "PacketParserNeuron.h"
#include "Runtime/Launch/Resources/Version.h"

const uint8 PacketParserNeuron::BoneCount = 59;

/**
* パケットでの登場順とボーンの対応付け
*/
const uint8 PacketParserNeuron::BoneIndices[] = {
	(uint8)EMocapNeuronBones::Hips,
	(uint8)EMocapNeuronBones::RightUpLeg,
	(uint8)EMocapNeuronBones::RightLeg,
	(uint8)EMocapNeuronBones::RightFoot,
	(uint8)EMocapNeuronBones::LeftUpLeg,
	(uint8)EMocapNeuronBones::LeftLeg,
	(uint8)EMocapNeuronBones::LeftFoot,
	(uint8)EMocapNeuronBones::Spine,
	(uint8)EMocapNeuronBones::Spine1,
	(uint8)EMocapNeuronBones::Spine2,
	(uint8)EMocapNeuronBones::Spine3,
	(uint8)EMocapNeuronBones::Neck,
	(uint8)EMocapNeuronBones::Head,
	(uint8)EMocapNeuronBones::RightShoulder,
	(uint8)EMocapNeuronBones::RightArm,
	(uint8)EMocapNeuronBones::RightForeArm,
	(uint8)EMocapNeuronBones::RightHand,
	(uint8)EMocapNeuronBones::RightHandThumb1,
	(uint8)EMocapNeuronBones::RightHandThumb2,
	(uint8)EMocapNeuronBones::RightHandThumb3,
	(uint8)EMocapNeuronBones::RightInHandIndex,
	(uint8)EMocapNeuronBones::RightHandIndex1,
	(uint8)EMocapNeuronBones::RightHandIndex2,
	(uint8)EMocapNeuronBones::RightHandIndex3,
	(uint8)EMocapNeuronBones::RightInHandMiddle,
	(uint8)EMocapNeuronBones::RightHandMiddle1,
	(uint8)EMocapNeuronBones::RightHandMiddle2,
	(uint8)EMocapNeuronBones::RightHandMiddle3,
	(uint8)EMocapNeuronBones::RightInHandRing,
	(uint8)EMocapNeuronBones::RightHandRing1,
	(uint8)EMocapNeuronBones::RightHandRing2,
	(uint8)EMocapNeuronBones::RightHandRing3,
	(uint8)EMocapNeuronBones::RightInHandPinky,
	(uint8)EMocapNeuronBones::RightHandPinky1,
	(uint8)EMocapNeuronBones::RightHandPinky2,
	(uint8)EMocapNeuronBones::RightHandPinky3,
	(uint8)EMocapNeuronBones::LeftShoulder,
	(uint8)EMocapNeuronBones::LeftArm,
	(uint8)EMocapNeuronBones::LeftForeArm,
	(uint8)EMocapNeuronBones::LeftHand,
	(uint8)EMocapNeuronBones::LeftHandThumb1,
	(uint8)EMocapNeuronBones::LeftHandThumb2,
	(uint8)EMocapNeuronBones::LeftHandThumb3,
	(uint8)EMocapNeuronBones::LeftInHandIndex,
	(uint8)EMocapNeuronBones::LeftHandIndex1,
	(uint8)EMocapNeuronBones::LeftHandIndex2,
	(uint8)EMocapNeuronBones::LeftHandIndex3,
	(uint8)EMocapNeuronBones::LeftInHandMiddle,
	(uint8)EMocapNeuronBones::LeftHandMiddle1,
	(uint8)EMocapNeuronBones::LeftHandMiddle2,
	(uint8)EMocapNeuronBones::LeftHandMiddle3,
	(uint8)EMocapNeuronBones::LeftInHandRing,
	(uint8)EMocapNeuronBones::LeftHandRing1,
	(uint8)EMocapNeuronBones::LeftHandRing2,
	(uint8)EMocapNeuronBones::LeftHandRing3,
	(uint8)EMocapNeuronBones::LeftInHandPinky,
	(uint8)EMocapNeuronBones::LeftHandPinky1,
	(uint8)EMocapNeuronBones::LeftHandPinky2,
	(uint8)EMocapNeuronBones::LeftHandPinky3,
};

///**
//* パケットでの登場順と親ボーンの対応付け
//*/
//const uint8 PacketParserNeuron::ParentBones [] = {
//	(uint8) EMocapNeuronBones::None,
//	(uint8) EMocapNeuronBones::Hips,
//	(uint8) EMocapNeuronBones::RightUpLeg,
//	(uint8) EMocapNeuronBones::RightLeg,
//	(uint8) EMocapNeuronBones::Hips,
//	(uint8) EMocapNeuronBones::LeftUpLeg,
//	(uint8) EMocapNeuronBones::LeftLeg,
//	(uint8) EMocapNeuronBones::Hips,
//	(uint8) EMocapNeuronBones::Spine,
//	(uint8) EMocapNeuronBones::Spine1,
//	(uint8) EMocapNeuronBones::Spine2,
//	(uint8) EMocapNeuronBones::Spine3,
//	(uint8) EMocapNeuronBones::Neck,
//	(uint8) EMocapNeuronBones::Spine3,
//	(uint8) EMocapNeuronBones::RightShoulder,
//	(uint8) EMocapNeuronBones::RightArm,
//	(uint8) EMocapNeuronBones::RightForeArm,
//	(uint8) EMocapNeuronBones::RightHand,
//	(uint8) EMocapNeuronBones::RightHandThumb1,
//	(uint8) EMocapNeuronBones::RightHandThumb2,
//	(uint8) EMocapNeuronBones::RightHand,
//	(uint8) EMocapNeuronBones::RightInHandIndex,
//	(uint8) EMocapNeuronBones::RightHandIndex1,
//	(uint8) EMocapNeuronBones::RightHandIndex2,
//	(uint8) EMocapNeuronBones::RightHand,
//	(uint8) EMocapNeuronBones::RightInHandMiddle,
//	(uint8) EMocapNeuronBones::RightHandMiddle1,
//	(uint8) EMocapNeuronBones::RightHandMiddle2,
//	(uint8) EMocapNeuronBones::RightHand,
//	(uint8) EMocapNeuronBones::RightInHandRing,
//	(uint8) EMocapNeuronBones::RightHandRing1,
//	(uint8) EMocapNeuronBones::RightHandRing2,
//	(uint8) EMocapNeuronBones::RightHand,
//	(uint8) EMocapNeuronBones::RightInHandPinky,
//	(uint8) EMocapNeuronBones::RightHandPinky1,
//	(uint8) EMocapNeuronBones::RightHandPinky2,
//	(uint8) EMocapNeuronBones::Spine3,
//	(uint8) EMocapNeuronBones::LeftShoulder,
//	(uint8) EMocapNeuronBones::LeftArm,
//	(uint8) EMocapNeuronBones::LeftForeArm,
//	(uint8) EMocapNeuronBones::LeftHand,
//	(uint8) EMocapNeuronBones::LeftHandThumb1,
//	(uint8) EMocapNeuronBones::LeftHandThumb2,
//	(uint8) EMocapNeuronBones::LeftHand,
//	(uint8) EMocapNeuronBones::LeftInHandIndex,
//	(uint8) EMocapNeuronBones::LeftHandIndex1,
//	(uint8) EMocapNeuronBones::LeftHandIndex2,
//	(uint8) EMocapNeuronBones::LeftHand,
//	(uint8) EMocapNeuronBones::LeftInHandMiddle,
//	(uint8) EMocapNeuronBones::LeftHandMiddle1,
//	(uint8) EMocapNeuronBones::LeftHandMiddle2,
//	(uint8) EMocapNeuronBones::LeftHand,
//	(uint8) EMocapNeuronBones::LeftInHandRing,
//	(uint8) EMocapNeuronBones::LeftHandRing1,
//	(uint8) EMocapNeuronBones::LeftHandRing2,
//	(uint8) EMocapNeuronBones::LeftHand,
//	(uint8) EMocapNeuronBones::LeftInHandPinky,
//	(uint8) EMocapNeuronBones::LeftHandPinky1,
//	(uint8) EMocapNeuronBones::LeftHandPinky2,
//};

/**
* モーキャプでは読み込まれないボーン
*/
const uint8 PacketParserNeuron::EmptyBoneIndices[] = {
	(uint8)EMocapBones::Root,
	(uint8)EMocapBones::Neck02,
	(uint8)EMocapBones::LeftThighTwist,
	(uint8)EMocapBones::LeftCalfTwist,
	(uint8)EMocapBones::LeftBall,
	(uint8)EMocapBones::RightThighTwist,
	(uint8)EMocapBones::RightCalfTwist,
	(uint8)EMocapBones::RightBall,
	(uint8)EMocapBones::LeftLowerArmTwist,
	(uint8)EMocapBones::LeftUpperArmTwist,
	(uint8)EMocapBones::RightLowerArmTwist,
	(uint8)EMocapBones::RightUpperArmTwist,
};

PacketParserNeuron::PacketParserNeuron() : PacketParser()
{
	Initialize();
}

PacketParserNeuron::~PacketParserNeuron()
{
}

//PacketParserNeuron::PacketParserNeuron(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//	Initialize();
//}

// Sets default values
void PacketParserNeuron::Initialize()
{
	this->SampleCount = 0;
}

/*  一つ分の受信データを解析し、AXIS Neuron の BVH データならば格納 */
bool PacketParserNeuron::Read(const FArrayReaderPtr& data, UMocapPose* pose)
{
	if (!CheckHeader(data)) return false;

	/* ヘッダーを読んだ時点でユーザーIDが分るので設定 */
	pose->UserId = this->userId;

	/* 読み込まれないボーンを空にする */
	for (int i = 0; i < (sizeof(EmptyBoneIndices) / sizeof(EmptyBoneIndices[0])); i++) {
		pose->BoneRotations[EmptyBoneIndices[i]] = FQuat(0, 0, 0, 1);
	}

	/* 読込開始 */
	const uint8* raw = data->GetData();
	int index = 64;

	/*  Refecence ありの場合、float16 × 6 がヘッダー後に存在するのでスキップ */
	if (this->hasReference) index += 24;

	/*  最初はルート位置が届く */
	FVector position = GetPosition(raw, index);
	pose->OriginalRootPosition = position;
	index += 12;

	/*  各関節の角度 */
	for (int i = 0; i < BoneCount; i++) {
		ProcessSegment(raw, i, index, pose);
		index += (this->hasDisplacement ? 24 : 12);
	}

	return true;
}

/* 一関節分の読込 */
void PacketParserNeuron::ProcessSegment(const uint8* data, const int32 segmentNo, const int32 index, UMocapPose* pose)
{
	int32 num = segmentNo;
	uint8 boneIndex = this->BoneIndices[num];
	FQuat quat = GetQuaternion(data, index);
	pose->BoneRotations[boneIndex] = quat;
}

/*  扱えるMVNのデータかヘッダを確認 */
bool PacketParserNeuron::CheckHeader(const FArrayReaderPtr& data)
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
	this->userId = GetUInt32(raw, index);
	index += 4;

	/*  ヘッダーの終了を確認 */
	if (GetUInt16(raw, 62) != 0xEEFF) return false;

	return true;
}

/* 座標をUEの座標系で返す */
FVector PacketParserNeuron::GetPosition(const uint8* data, const int32 index)
{
	return FVector(
		GetFloat(data, index),
		GetFloat(data, index + 8),
		GetFloat(data, index + 4)
		);
}

/**
* 姿勢をUEの座標系で返す。AXIS Neuron では YXZ の順としておくこと！
*/
FQuat PacketParserNeuron::GetQuaternion(const uint8* data, const int32 index)
{
	/* deg を rad にし、さらに半分にする係数*/
	static const float halfRadCoef = HALF_PI / 180.0f;

	/*  BVH 右手系 YXZ -> UE4 左手系 ZXY */
	FVector euler = FVector();
	euler.Z = -GetFloat(data, index);
	euler.X = -GetFloat(data, index + 4);
	euler.Y = -GetFloat(data, index + 8);

	float sx, sy, sz, cx, cy, cz;

#if (ENGINE_MAJOR_VERSION >= 4) && (ENGINE_MINOR_VERSION >= 8)
	FMath::SinCos(&sx, &cx, euler.X * halfRadCoef);
	FMath::SinCos(&sy, &cy, euler.Y * halfRadCoef);
	FMath::SinCos(&sz, &cz, euler.Z * halfRadCoef);
#else
	sx = FMath::Sin(euler.X * halfRadCoef);
	sy = FMath::Sin(euler.Y * halfRadCoef);
	sz = FMath::Sin(euler.Z * halfRadCoef);
	cx = FMath::Cos(euler.X * halfRadCoef);
	cy = FMath::Cos(euler.Y * halfRadCoef);
	cz = FMath::Cos(euler.Z * halfRadCoef);
#endif

	FQuat qx = FQuat(sx, 0, 0, cx);
	FQuat qy = FQuat(0, sy, 0, cy);
	FQuat qz = FQuat(0, 0, sz, cz);

	FQuat quat = qz * qx * qy;

	return quat;
}
