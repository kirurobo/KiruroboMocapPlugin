// Copyright (c) 2015 Kirurobo

#pragma once

#include "MocapBones.h"
//#include "CoreUObject.h"
//#include "PacketReader.generated.h"


/**
 * UDP receiver base class
 */
class UPacketReader //: public UObject
{
public:
	UPacketReader();
	~UPacketReader();

protected:
	int8 BoneNumber = 0;

	/*  初回受信ならtrue。オフセットの取得時に使う */
	bool IsFirstReceive = true;

	virtual void Initialize();

	/*  関節一つ分を解析 */
	void ProcessSegment(const uint8* data, const int32 segmentNo);

	/*  floatとして解釈 */
	float GetFloat(const uint8* data, const int32 index);

	/*  int32として解釈 */
	int32 GetInt32(const uint8* data, const int32 index);

	/*  uint32として解釈 */
	uint32 GetUInt32(const uint8* data, const int32 index);

	/*  uint16として解釈 */
	uint16 GetUInt16(const uint8* data, const int32 index);

	/*  ビッグエンディアンで届いたfloatとして解釈 */
	float GetBigEndianFloat(const uint8* data, const int32 index);

	/*  ビッグエンディアンで届いたint32として解釈 */
	int32 GetBigEndianInt32(const uint8* data, const int32 index);

	/*  UDPパケットのヘッダを確認 */
	virtual bool CheckHeader(const FArrayReaderPtr& data);

public:

	/*  受信データ1つ分を解析 */
	virtual bool Read(const FArrayReaderPtr& data);

	/*  UDPパケットのヘッダを確認 */
	virtual void ResetOffset();

	TArray<FQuat> lastRotations;
	TArray<FQuat> BoneRotations;
	FVector RootPosition = FVector(0, 0, 0);
	FVector PositionOffset = FVector(0, 0, 0);

};


