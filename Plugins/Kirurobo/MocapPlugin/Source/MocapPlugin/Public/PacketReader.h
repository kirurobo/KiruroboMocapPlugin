// Copyright (c) 2015 Kirurobo

#pragma once

#include "MocapBones.h"
#include "MocapPose.h"


/**
 * UDPパケット解釈を担うクラス
 */
class UPacketReader //: public UObject
{
public:
	UPacketReader();
	~UPacketReader();

protected:
	/* ユーザーID */
	int32 userId = 0;

	virtual void Initialize();

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

	/*  受信データ1つ分を解析してMocapPoseに格納 */
	virtual bool Read(const FArrayReaderPtr& data, UMocapPose* pose);
};


