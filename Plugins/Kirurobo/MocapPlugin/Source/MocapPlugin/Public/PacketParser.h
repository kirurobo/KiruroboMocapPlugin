// Copyright (c) 2015-2016 Kirurobo

#pragma once

#include "MocapBones.h"
#include "MocapPose.h"
#include "Networking.h"

/**
* UDPパケット解釈を担うクラス
*/
class PacketParser
{
public:
	PacketParser();
	~PacketParser();

protected:
	/* ユーザーID */
	int32 userId = 0;

	void Initialize();

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
	virtual bool CheckHeader(const uint8* data, const int32 length);

public:
	/* 複数のモーキャプを利用した際に区別するため、ユーザーIDに加える数 */
	int32 UserIdOffset = 0;

	/*  受信データ1つ分を解析してMocapPoseに格納 */
	virtual bool Read(const uint8* data, int32 length, UMocapPose* pose);
};
