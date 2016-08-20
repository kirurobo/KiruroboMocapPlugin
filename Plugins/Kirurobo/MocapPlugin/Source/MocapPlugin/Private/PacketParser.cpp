// Copyright (c) 2015-2016 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "PacketParser.h"

PacketParser::PacketParser()
{
	Initialize();
}

PacketParser::~PacketParser()
{
}

void PacketParser::Initialize()
{
}

/*  一つ分の受信データを解析し、正しければ格納 */
bool PacketParser::Read(const uint8* data, const int32 length, UMocapPose* pose)
{
	if (!CheckHeader(data, length)) return false;
	return true;
}

/*  扱えるデータかヘッダを確認 */
bool PacketParser::CheckHeader(const uint8* data, const int32 length)
{
	return false;
}

//------------------------------------------------------------------------------------
/*  整数として返す */
int32 PacketParser::GetInt32(const uint8* data, const int32 index)
{
	uint8 value[4];
	int32* pInt;
	value[3] = data[index + 3];
	value[2] = data[index + 2];
	value[1] = data[index + 1];
	value[0] = data[index + 0];
	pInt = (int32*)value;
	return *pInt;
}

/*  整数として返す */
uint32 PacketParser::GetUInt32(const uint8* data, const int32 index)
{
	uint8 value[4];
	uint32* pInt;
	value[3] = data[index + 3];
	value[2] = data[index + 2];
	value[1] = data[index + 1];
	value[0] = data[index + 0];
	pInt = (uint32*)value;
	return *pInt;
}

uint16 PacketParser::GetUInt16(const uint8* data, const int32 index)
{
	uint8 value[4];
	uint16* pData;
	value[3] = data[index + 3];
	value[2] = data[index + 2];
	value[1] = data[index + 1];
	value[0] = data[index + 0];
	pData = (uint16*)value;
	return *pData;
}

/*  実数として返す */
float PacketParser::GetFloat(const uint8* data, const int32 index)
{
	uint8 value[4];
	float* pFloat;
	value[3] = data[index + 3];
	value[2] = data[index + 2];
	value[1] = data[index + 1];
	value[0] = data[index + 0];
	pFloat = (float*)value;
	return *pFloat;
}

/*  ビッグエンディアンをリトルエンディアンに直し、整数として返す */
int32 PacketParser::GetBigEndianInt32(const uint8* data, const int32 index)
{
	uint8 value[4];
	int32* pInt;
	value[3] = data[index + 0];
	value[2] = data[index + 1];
	value[1] = data[index + 2];
	value[0] = data[index + 3];
	pInt = (int32*)value;
	return *pInt;
}

/*  ビッグエンディアンをリトルエンディアンに直し、実数として返す */
float PacketParser::GetBigEndianFloat(const uint8* data, const int32 index)
{
	uint8 value[4];
	float* pFloat;
	value[3] = data[index + 0];
	value[2] = data[index + 1];
	value[1] = data[index + 2];
	value[0] = data[index + 3];
	pFloat = (float*)value;
	return *pFloat;
}
