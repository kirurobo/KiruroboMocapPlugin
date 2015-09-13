// Copyright (c) 2015 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "PacketReader.h"


//UPacketReader::UPacketReader(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//	Initialize();
//}

UPacketReader::UPacketReader()
{
	Initialize();
}

void UPacketReader::Initialize()
{
	/*  ボーン総数を取得 */
	UEnum* pMocapBones = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMocapBones"), true);
	this->BoneNumber = pMocapBones->NumEnums();

	/*  初期化 */
	this->RootPosition = FVector::ZeroVector;
	this->PositionOffset = FVector::ZeroVector;
	this->IsFirstReceive = true;
}

/*  一つ分の受信データを解析し、正しければ格納 */
bool UPacketReader::Read(const FArrayReaderPtr& data)
{
	if (!CheckHeader(data)) return false;

	const uint8* raw = data->GetData();

	for (int i = 0; i < this->BoneNumber; i++) {
		ProcessSegment(raw, i);
	}

	/*  初回の受信ならばオフセットを設定 */
	if (IsFirstReceive) {
		this->PositionOffset = -this->RootPosition;
		this->IsFirstReceive = false;
	}

	return true;
}

void UPacketReader::ProcessSegment(const uint8* data, const int32 segmentNo)
{
}

/*  扱えるデータかヘッダを確認 */
bool UPacketReader::CheckHeader(const FArrayReaderPtr& data)
{
	return false;
}

/**
* オフセットを現在の基準座標を元に決定
*/
void UPacketReader::ResetOffset()
{
	this->IsFirstReceive = true;
}

//------------------------------------------------------------------------------------
/*  整数として返す */
int32 UPacketReader::GetInt32(const uint8* data, const int32 index)
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
uint32 UPacketReader::GetUInt32(const uint8* data, const int32 index)
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

uint16 UPacketReader::GetUInt16(const uint8* data, const int32 index)
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
float UPacketReader::GetFloat(const uint8* data, const int32 index)
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
int32 UPacketReader::GetBigEndianInt32(const uint8* data, const int32 index)
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
float UPacketReader::GetBigEndianFloat(const uint8* data, const int32 index)
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
