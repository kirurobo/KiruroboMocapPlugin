// Copyright (c) 2015-2016 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "MocapReceiver.h"


UMocapReceiver::UMocapReceiver( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	Initialize();
}

UMocapReceiver::~UMocapReceiver()
{
	for (int i = 0; i < this->Parsers.Num(); i++) {
		delete this->Parsers[i];
	}
}

// Sets default values
void UMocapReceiver::Initialize()
{
	this->IdentityPose = NewObject<UMocapPose>();

	this->Parsers.Add(new PacketParserMvn());
	this->Parsers.Add(new PacketParserNeuron());

	/* 受信されたデータの保存領域 */
	CurrentPose = this->IdentityPose;
}


/**
* 受信を開始
*/
bool UMocapReceiver::Connect()
{
	bool connected = false;
	for (int i = 0; i < this->Sockets.Num(); i++) {
		if (this->Sockets[i]->Connect()) {
			this->Sockets[i]->SetParent(this);	/* 接続と同時に親を設定 */
			connected = true;
		}
	}
	return connected;
}

/**
* 受信を終了してポートを閉じる
*/
void UMocapReceiver::Close()
{
	for (int i = 0; i < this->Sockets.Num(); i++) {
		this->Sockets[i]->Close();
	}
}

/**
* データが届いた際の読み込み処理
*/
bool UMocapReceiver::Parse(const uint8* raw, const int32 length)
{
	bool received = false;
	
	/* モーキャプソフト毎にその形式か調べて受信する */
	for (int i = 0; i < this->Parsers.Num(); i++) {
		PacketParser* parser = this->Parsers[i];
		if (parser->Read(raw, length, this->CurrentPose)) {
			received = true;
			break;
		}
	}
	if (!received) return false;

	/* 受信できたらユーザーID毎に保存する */
	int userId = this->CurrentPose->UserId;

	UMocapPose** pPose = this->PoseMap.Find(userId);
	if (pPose == nullptr) {
		/*  初回受信。現在の位置が原点となるようオフセットを設定 */
		//this->CurrentPose->PositionOffset = -this->CurrentPose->OriginalRootPosition;
		UMocapPose* pose = this->CurrentPose->Clone();
		pose->PositionOffset = -pose->OriginalRootPosition;
		if (this->PoseMap.Num() < 1) {
			this->CurrentPose->PositionOffset = pose->PositionOffset;
		}
		this->Poses.Add(pose);				/* GCで削除されるのを防ぐため、こちらにも登録 */
		this->PoseMap.Add(userId, pose);
	}
	else {
		/* 既に受信されたユーザーならば値の複製のみ */
		this->CurrentPose->CopyTo(*pPose);
	}
	return true;
}

/* 指定されたユーザーIDの姿勢を返す */
UMocapPose* UMocapReceiver::GetMocapPose(const int32 userId)
{
	if (this->CurrentPose == nullptr) return this->IdentityPose;
	if (userId < 0) return this->CurrentPose;
	UMocapPose** pPose =  this->PoseMap.Find(userId);
	if (pPose == nullptr) {
		return this->IdentityPose;
	}
	else {
		return *pPose;
	}
}
