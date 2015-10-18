// Copyright (c) 2015 Kirurobo

#pragma once

#include "PacketReader.h"
//#include "PacketReaderMvn.generated.h"

/**
 * MVN Quaternion protocol reader
 */
//UCLASS(ClassGroup = MocapPlugin)
class UPacketReaderMvn : public UPacketReader
{
	//GENERATED_UCLASS_BODY()

public:
	UPacketReaderMvn();
	virtual ~UPacketReaderMvn();

	const static uint8 BoneCount;			/* モーキャプで受信されるボーン数 */
	const static uint8 BoneIndices [];		/* モーキャプで受信される順番のボーン */
	const static uint8 ParentBones [];		/* モーキャプで受信されるボーンの親ボーン */
	const static uint8 EmptyBoneIndices [];	/* モーキャプでは受信されず、常に空とすべきボーン */

protected:
	/* UDPパケットの通し番号 */
	int32 SampleCount;

	/* 受信されてきた元の回転（ワールド座標系での絶対姿勢） */
	TArray<FQuat> rotations;

	/* 初期化処理 */
	void Initialize();

	/*  関節一つ分を解析 */
	void ProcessSegment(const uint8* data, const int32 segmentNo, UMocapPose* pose);

	/* バイト列をクォータニオンで解釈 */
	FQuat GetQuaternion(const uint8* data, const int32 index);

	/* バイト列を座標として解釈 */
	FVector GetPosition(const uint8* data, const int32 index);

	/*  UDPパケットのヘッダを確認 */
	bool CheckHeader(const FArrayReaderPtr& data);

public:

	/*  受信データ1つ分を解析 */
	bool Read(const FArrayReaderPtr& data, UMocapPose* pose);
};


