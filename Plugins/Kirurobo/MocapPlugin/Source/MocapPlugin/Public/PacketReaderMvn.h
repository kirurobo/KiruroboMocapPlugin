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

	const static uint8 BoneCount;
	const static uint8 BoneIndices[];
	const static uint8 ParentBones[];

protected:
	
	int32 SampleCount;
	TArray<FQuat> lastRotations;

	void Initialize();

	/*  関節一つ分を解析 */
	void ProcessSegment(const uint8* data, const int32 segmentNo);

	FQuat GetQuaternion(const uint8* data, const int32 index);

	FVector GetPosition(const uint8* data, const int32 index);

	/*  UDPパケットのヘッダを確認 */
	bool CheckHeader(const FArrayReaderPtr& data);

public:

	/*  受信データ1つ分を解析 */
	bool Read(const FArrayReaderPtr& data);
};


