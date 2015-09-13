// Copyright (c) 2015 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "PacketReaderMvn.h"


const uint8 UPacketReaderMvn::BoneCount = 23;

/**
* パケットでの登場順とボーンの対応付け
*/
const uint8 UPacketReaderMvn::BoneIndices[] = {
	(uint8)EMocapMvnBones::Pelvis,
	(uint8)EMocapMvnBones::L5,
	(uint8)EMocapMvnBones::L3,
	(uint8)EMocapMvnBones::T12,
	(uint8)EMocapMvnBones::T8,
	(uint8)EMocapMvnBones::Neck,
	(uint8)EMocapMvnBones::Head,
	(uint8)EMocapMvnBones::RightShoulder,
	(uint8)EMocapMvnBones::RightUpperArm,
	(uint8)EMocapMvnBones::RightForeArm,
	(uint8)EMocapMvnBones::RightHand,
	(uint8)EMocapMvnBones::LeftShoulder,
	(uint8)EMocapMvnBones::LeftUpperArm,
	(uint8)EMocapMvnBones::LeftForeArm,
	(uint8)EMocapMvnBones::LeftHand,
	(uint8)EMocapMvnBones::RightUpperLeg,
	(uint8)EMocapMvnBones::RightLowerLeg,
	(uint8)EMocapMvnBones::RightFoot,
	(uint8)EMocapMvnBones::RightToe,
	(uint8)EMocapMvnBones::LeftUpperLeg,
	(uint8)EMocapMvnBones::LeftLowerLeg,
	(uint8)EMocapMvnBones::LeftFoot,
	(uint8)EMocapMvnBones::LeftToe,
};

/**
* パケットでの登場順と親ボーンの対応付け
*/
const uint8 UPacketReaderMvn::ParentBones[] = {
	(uint8)EMocapMvnBones::None,
	(uint8)EMocapMvnBones::Pelvis,
	(uint8)EMocapMvnBones::L5,
	(uint8)EMocapMvnBones::L3,
	(uint8)EMocapMvnBones::T12,
	(uint8)EMocapMvnBones::T8,
	(uint8)EMocapMvnBones::Neck,
	(uint8)EMocapMvnBones::T8,
	(uint8)EMocapMvnBones::RightShoulder,
	(uint8)EMocapMvnBones::RightUpperArm,
	(uint8)EMocapMvnBones::RightForeArm,
	(uint8)EMocapMvnBones::T8,
	(uint8)EMocapMvnBones::LeftShoulder,
	(uint8)EMocapMvnBones::LeftUpperArm,
	(uint8)EMocapMvnBones::LeftForeArm,
	(uint8)EMocapMvnBones::Pelvis,
	(uint8)EMocapMvnBones::RightUpperLeg,
	(uint8)EMocapMvnBones::RightLowerLeg,
	(uint8)EMocapMvnBones::RightFoot,
	(uint8)EMocapMvnBones::Pelvis,
	(uint8)EMocapMvnBones::LeftUpperLeg,
	(uint8)EMocapMvnBones::LeftLowerLeg,
	(uint8)EMocapMvnBones::LeftFoot,
};


UPacketReaderMvn::UPacketReaderMvn() : UPacketReader()
{
	Initialize();
}

//UPacketReaderMvn::UPacketReaderMvn(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//	Initialize();
//}

// Sets default values
void UPacketReaderMvn::Initialize()
{
	/*  サンプルカウンタ */
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

/*  一つ分の受信データを解析し、MVNの値ならば格納 */
bool UPacketReaderMvn::Read(const FArrayReaderPtr& data)
{
	if (!CheckHeader(data)) return false;

	const uint8* raw = data->GetData();

	for (int i = 0; i < BoneCount; i++) {
		ProcessSegment(raw, i);
	}

	return true;
}

void UPacketReaderMvn::ProcessSegment(const uint8* data, const int32 segmentNo)
{
	/*  1関節あたり32バイト＋ヘッダ24バイトが、見るべきインデックスの始点 */
	int32 index = segmentNo * 32 + 24;

	/*  関節番号 */
	int32 num = GetBigEndianInt32(data, index) - 1;
	if (num < 0 || num >= BoneCount) return;

	/*  関節座標を取得 */
	if (num == 0) {
		FVector position = GetPosition(data, index + 4);

		/*  初回受信ならオフセットを記憶 */
		if (this->IsFirstReceive) {
			this->PositionOffset = -position;
			this->IsFirstReceive = false;
		}
		this->RootPosition = position + this->PositionOffset;

		//UE_LOG(LogTemp, Log, TEXT("Root position: %f %f %f"), this->RootPosition.X, this->RootPosition.Y, this->RootPosition.Z);
	}

	FQuat quat = GetQuaternion(data, index + 16);

	/*  統一関節番号と親関節番号を取得 */
	uint8 boneIndex = BoneIndices[num];
	uint8 parentIndex = ParentBones[num];

	if (parentIndex != EMocapMvnBones::None) {
		FQuat localQuat = lastRotations[parentIndex].Inverse() * quat;
		this->BoneRotations[boneIndex] = localQuat;
		this->lastRotations[boneIndex] = quat;
	}
	else {
		this->BoneRotations[boneIndex] = quat;
		this->lastRotations[boneIndex] = quat;
	}
}

/**
* 扱えるMVNのデータかヘッダを確認
*/
bool UPacketReaderMvn::CheckHeader(const FArrayReaderPtr& data)
{
	/*  ヘッダ部の長さ未満なら不正として終了 */
	if (data->Num() < 24) return false;

	const uint8* raw = data->GetData();
	int32 index = 0;

	/*  先頭の文字列を確認 */
	if (raw[0] != 'M' || raw[1] != 'X' || raw[2] != 'T' || raw[3] != 'P' || raw[4] != '0' || raw[5] != '2') return false;

	/*  サンプルカウンタを確認 */
	index = 6;
	int32 count = GetBigEndianInt32(raw, index);
	if ((count < this->SampleCount) && ((this->SampleCount - count) >= 4)) {
		/*  前回のカウンタよりも小さく、それが4フレーム以内ならば古いデータとみなして破棄する。 */
		/* 	あまり大きな差があれば、MVNを再起動した可能性があるので破棄せず採用する。 */
		return false;
	}
	this->SampleCount = count;

	/*  セグメント数をチェック */
	index += 5;
	if (raw[index] < BoneCount) return false;

	return true;
}

/*  MVN座標系のクォータニオンをUEのクォータニオンとして返す */
FQuat UPacketReaderMvn::GetQuaternion(const uint8* data, const int32 index)
{
	return FQuat(
		-GetBigEndianFloat(data, index + 8),
		-GetBigEndianFloat(data, index + 4),
		-GetBigEndianFloat(data, index + 12),
		GetBigEndianFloat(data, index)
		);
}

/*  MVNの座標をUEの座標系で返す */
FVector UPacketReaderMvn::GetPosition(const uint8* data, const int32 index)
{
	return FVector(
		GetBigEndianFloat(data, index + 4) * 100.0,		/*  [m] を [cm] にする */
		GetBigEndianFloat(data, index) * 100.0,
		GetBigEndianFloat(data, index + 8) * 100.0
		);
}
