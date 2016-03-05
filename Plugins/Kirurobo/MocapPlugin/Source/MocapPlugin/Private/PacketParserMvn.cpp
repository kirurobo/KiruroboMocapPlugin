// Copyright (c) 2015-2016 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "PacketParserMvn.h"

const uint8 PacketParserMvn::BoneCount = 23;

/**
* パケットでの登場順とボーンの対応付け
*/
const uint8 PacketParserMvn::BoneIndices[] = {
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
const uint8 PacketParserMvn::ParentBones[] = {
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

/**
* モーキャプで読み込まれないボーン
*/
const uint8 PacketParserMvn::EmptyBoneIndices[] = {
	(uint8)EMocapBones::Root,
	(uint8)EMocapBones::Neck02,
	(uint8)EMocapBones::LeftThighTwist,
	(uint8)EMocapBones::LeftCalfTwist,
	(uint8)EMocapBones::RightThighTwist,
	(uint8)EMocapBones::RightCalfTwist,
	(uint8)EMocapBones::LeftLowerArmTwist,
	(uint8)EMocapBones::LeftUpperArmTwist,
	(uint8)EMocapBones::LeftThumb01,
	(uint8)EMocapBones::LeftThumb02,
	(uint8)EMocapBones::LeftThumb03,
	(uint8)EMocapBones::LeftInHandIndex,
	(uint8)EMocapBones::LeftIndex01,
	(uint8)EMocapBones::LeftIndex02,
	(uint8)EMocapBones::LeftIndex03,
	(uint8)EMocapBones::LeftInHandMiddle,
	(uint8)EMocapBones::LeftMiddle01,
	(uint8)EMocapBones::LeftMiddle02,
	(uint8)EMocapBones::LeftMiddle03,
	(uint8)EMocapBones::LeftInHandRing,
	(uint8)EMocapBones::LeftRing01,
	(uint8)EMocapBones::LeftRing02,
	(uint8)EMocapBones::LeftRing03,
	(uint8)EMocapBones::LeftInHandPinky,
	(uint8)EMocapBones::LeftPinky01,
	(uint8)EMocapBones::LeftPinky02,
	(uint8)EMocapBones::LeftPinky03,
	(uint8)EMocapBones::RightLowerArmTwist,
	(uint8)EMocapBones::RightUpperArmTwist,
	(uint8)EMocapBones::RightThumb01,
	(uint8)EMocapBones::RightThumb02,
	(uint8)EMocapBones::RightThumb03,
	(uint8)EMocapBones::RightInHandIndex,
	(uint8)EMocapBones::RightIndex01,
	(uint8)EMocapBones::RightIndex02,
	(uint8)EMocapBones::RightIndex03,
	(uint8)EMocapBones::RightInHandMiddle,
	(uint8)EMocapBones::RightMiddle01,
	(uint8)EMocapBones::RightMiddle02,
	(uint8)EMocapBones::RightMiddle03,
	(uint8)EMocapBones::RightInHandRing,
	(uint8)EMocapBones::RightRing01,
	(uint8)EMocapBones::RightRing02,
	(uint8)EMocapBones::RightRing03,
	(uint8)EMocapBones::RightInHandPinky,
	(uint8)EMocapBones::RightPinky01,
	(uint8)EMocapBones::RightPinky02,
	(uint8)EMocapBones::RightPinky03,
};

PacketParserMvn::PacketParserMvn() : PacketParser()
{
	Initialize();
}

PacketParserMvn::~PacketParserMvn()
{
}

// Sets default values
void PacketParserMvn::Initialize()
{
	/*  サンプルカウンタ */
	this->SampleCount = 0;

	/* 元回転の配列を準備 */
	UEnum* pBones = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMocapBones"), true);
	int count = pBones->NumEnums();
	this->rotations.Reserve(count);
	for (int i = 0; i < count; i++) {
		this->rotations.Add(FQuat(0, 0, 0, 1));
	}
}

/*  一つ分の受信データを解析し、MVNの値ならば格納 */
bool PacketParserMvn::Read(const uint8* raw, const int32 length, UMocapPose* pose)
{
	if (!CheckHeader(raw, length)) return false;

	/* ヘッダーを読んだ時点でユーザーIDが分るので設定 */
	pose->UserId = this->userId;

	/* 読み込まれないボーンを空にする */
	for (int i = 0; i < (sizeof(EmptyBoneIndices) / sizeof(EmptyBoneIndices[0])); i++) {
		pose->BoneRotations[EmptyBoneIndices[i]] = FQuat(0, 0, 0, 1);
	}

	/* 読込開始 */
	for (int i = 0; i < BoneCount; i++) {
		ProcessSegment(raw, i, pose);
	}

	return true;
}

void PacketParserMvn::ProcessSegment(const uint8* data, const int32 segmentNo, UMocapPose* pose)
{
	/*  1関節あたり32バイト＋ヘッダ24バイトが、見るべきインデックスの始点 */
	int32 index = segmentNo * 32 + 24;

	/*  関節番号 */
	int32 num = GetBigEndianInt32(data, index) - 1;
	if (num < 0 || num >= BoneCount) return;

	/*  最初の関節（Pelvis）ならば関節座標を取得 */
	if (num == 0) {
		FVector position = GetPosition(data, index + 4);
		pose->OriginalRootPosition = position;
		//UE_LOG(LogTemp, Log, TEXT("Root position: %f %f %f"), this->RootPosition.X, this->RootPosition.Y, this->RootPosition.Z);
	}

	FQuat quat = GetQuaternion(data, index + 16);

	/*  統一関節番号と親関節番号を取得 */
	uint8 boneIndex = BoneIndices[num];
	uint8 parentIndex = ParentBones[num];

	if (parentIndex != EMocapMvnBones::None) {
		FQuat localQuat = this->rotations[parentIndex].Inverse() * quat;
		pose->BoneRotations[boneIndex] = localQuat;
		this->rotations[boneIndex] = quat;
	}
	else {
		pose->BoneRotations[boneIndex] = quat;
		this->rotations[boneIndex] = quat;
	}
}

/**
* 扱えるMVNのデータかヘッダを確認
*/
bool PacketParserMvn::CheckHeader(const uint8* raw, const int32 length)
{
	/*  ヘッダ部の長さ未満なら不正として終了 */
	if (length < 24) return false;

	int32 index = 0;

	/*  先頭の文字列を確認（6バイト） */
	if (raw[0] != 'M' || raw[1] != 'X' || raw[2] != 'T' || raw[3] != 'P' || raw[4] != '0' || raw[5] != '2') return false;
	index += 6;

	/*  サンプルカウンタを確認（4バイト） */
	int32 count = GetBigEndianInt32(raw, index);
	if ((count < this->SampleCount) && ((this->SampleCount - count) <= 15)) {
		/*  前回のカウンタよりも小さく、それが15フレーム以内ならば古いデータとみなして破棄する。 */
		/* 	あまり大きな差があれば、MVNを再起動した可能性があるので破棄せず採用する。 */
		return false;
	}
	this->SampleCount = count;
	index += 4;

	/* データグラムカウンタ（1バイト） */
	index += 1;

	/*  セグメント数（1バイト） */
	if (raw[index] < BoneCount) return false;
	index += 1;

	/* タイムコード（4バイト） */
	index += 4;

	/* アバターID（1バイト） */
	this->userId = raw[index];
	index += 1;

	/* 予約領域（7バイト） */

	return true;
}

/*  MVN座標系のクォータニオンをUEのクォータニオンとして返す */
FQuat PacketParserMvn::GetQuaternion(const uint8* data, const int32 index)
{
	return FQuat(
		-GetBigEndianFloat(data, index + 8),
		-GetBigEndianFloat(data, index + 4),
		-GetBigEndianFloat(data, index + 12),
		GetBigEndianFloat(data, index)
		);
}

/*  MVNの座標をUEの座標系で返す */
FVector PacketParserMvn::GetPosition(const uint8* data, const int32 index)
{
	return FVector(
		GetBigEndianFloat(data, index + 4) * 100.0,		/*  [m] を [cm] にする */
		GetBigEndianFloat(data, index) * 100.0,
		GetBigEndianFloat(data, index + 8) * 100.0
		);
}
