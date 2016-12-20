// Copyright (c) 2015 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "PacketReader.h"


//FPacketReader::FPacketReader(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//	Initialize();
//}

FPacketReader::FPacketReader()
{
	Initialize();
}

FPacketReader::~FPacketReader()
{
}

void FPacketReader::Initialize()
{
}

/*  一つ分の受信データを解析し、正しければ格納 */
bool FPacketReader::Read(const FArrayReaderPtr& data, UMocapPose* pose)
{
	if (!CheckHeader(data)) return false;

	const uint8* raw = data->GetData();

	return true;
}

/*  扱えるデータかヘッダを確認 */
bool FPacketReader::CheckHeader(const FArrayReaderPtr& data)
{
	return false;
}

//------------------------------------------------------------------------------------
/*  整数として返す */
int32 FPacketReader::GetInt32(const uint8* data, const int32 index)
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
uint32 FPacketReader::GetUInt32(const uint8* data, const int32 index)
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

uint16 FPacketReader::GetUInt16(const uint8* data, const int32 index)
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
float FPacketReader::GetFloat(const uint8* data, const int32 index)
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
int32 FPacketReader::GetBigEndianInt32(const uint8* data, const int32 index)
{
	uint8 value[4];
	int32* pInt;
	value[3] = data[index + 0];
	value[2] = data[index + 1];
	value[1] = data[index + 2];
	value[0] = data[index + 3];
	pInt = (int32*) value;
	return *pInt;
}

/*  ビッグエンディアンをリトルエンディアンに直し、実数として返す */
float FPacketReader::GetBigEndianFloat(const uint8* data, const int32 index)
{
	uint8 value[4];
	float* pFloat;
	value[3] = data[index + 0];
	value[2] = data[index + 1];
	value[1] = data[index + 2];
	value[0] = data[index + 3];
	pFloat = (float*) value;
	return *pFloat;
}
