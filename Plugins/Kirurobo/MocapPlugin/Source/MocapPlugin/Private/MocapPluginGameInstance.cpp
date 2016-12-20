// Copyright (c) 2015 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "MocapPluginGameInstance.h"


/*  初期化 */
void UMocapPluginGameInstance::Init()
{
	UE_LOG(LogInit, Warning, TEXT("Initialize MocapPluginGameInstance."));
	this->MocapReceiver = NewObject<UMocapReceiver>();
	this->Connect();
}

/*  終了時の処理 */
void UMocapPluginGameInstance::Shutdown()
{
	this->Close();
}

/*  指定ポートに接続 */
bool UMocapPluginGameInstance::Connect(int32 port)
{
	if (port > 0) {
		this->PortNo = port;
	}

	if (this->MocapReceiver != NULL) {
		this->MocapReceiver->Close();

		this->MocapReceiver->Port = this->PortNo;
		this->MocapReceiver->MvnUserIdOffset = this->MvnUserIdOffset;
		this->MocapReceiver->NeuronUserIdOffset = this->NeuronUserIdOffset;
		this->MocapReceiver->KinectUserIdOffset = this->KinectUserIdOffset;

		UE_LOG(LogInit, Warning, TEXT("Connect UDP receiver in MocapPluginGameInstance."));
		return this->MocapReceiver->Connect();
	}
	return false;
}

/*  接続を閉じる */
void UMocapPluginGameInstance::Close()
{
	if (this->MocapReceiver != NULL) {
		this->MocapReceiver->Close();
	}
}


//------------------------------------------------------------------------------------
/*  静的メソッド */


/*  モデルの座標取得 */
FVector UMocapPluginGameInstance::GetRootPosition(const int32 userId, const UMocapPluginGameInstance* instance)
{
	if (instance == NULL || instance->MocapReceiver == NULL) {
		return FVector::ZeroVector;
	}

	return instance->MocapReceiver->GetMocapPose(userId)->GetRootPosition();
}
