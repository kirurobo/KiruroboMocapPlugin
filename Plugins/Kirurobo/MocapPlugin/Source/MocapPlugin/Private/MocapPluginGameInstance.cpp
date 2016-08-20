// Copyright (c) 2015-2016 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "MocapPluginGameInstance.h"


/*  初期化 */
void UMocapPluginGameInstance::Init()
{
	Super::Init();


	this->MocapReceiver = NewObject<UMocapReceiver>();

	UMocapUdpSocket* socket = NewObject<UMocapUdpSocket>();
	//socket->ParentReceiver = this->MocapReceiver;
	socket->Port = 9763;
	this->Sockets.Add(socket);

	UMocapUdpSocket* neuronSocket = NewObject<UMocapUdpSocket>();
	//neuronSocket->ParentReceiver = this->MocapReceiver;
	neuronSocket->Port = 7001;
	this->Sockets.Add(neuronSocket);

	this->MocapReceiver->Sockets = this->Sockets;

	this->Connect();
}

/*  終了時の処理 */
void UMocapPluginGameInstance::Shutdown()
{
	Super::Shutdown();

	this->Close();
}

/*  指定ポートに接続 */
bool UMocapPluginGameInstance::Connect()
{
	//UE_LOG(LogInit, Log, TEXT("MocapPluginGameInstance connect!"));

	if (this->MocapReceiver != NULL) {
		this->MocapReceiver->Close();

		this->MocapReceiver->MvnUserIdOffset = this->MvnUserIdOffset;
		this->MocapReceiver->NeuronUserIdOffset = this->NeuronUserIdOffset;
		this->MocapReceiver->KinectUserIdOffset = this->KinectUserIdOffset;

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

/*  モデルの座標取得 */
const FVector UMocapPluginGameInstance::GetRootPosition(const int32 userId)
{
	if (this->MocapReceiver == NULL) {

		// 接続がないのに取得要求があった場合は警告
		UE_LOG(LogTemp, Warning, TEXT("MocapReceiver is null"));

		return FVector::ZeroVector;
	}

	return this->MocapReceiver->GetMocapPose(userId)->GetRootPosition();
}


/**
* 指定ボーンのFRotatorを取得
*/
const FRotator UMocapPluginGameInstance::GetBoneRotator(const EMocapBones::Type bone, const int32 userId)
{
	if (this->MocapReceiver == NULL) {

		// 接続がないのに取得要求があった場合は警告
		UE_LOG(LogTemp, Warning, TEXT("MocapReceiver is null"));

		return FRotator::ZeroRotator;
	}
	return this->MocapReceiver->GetMocapPose(userId)->BoneRotations[bone].Rotator();
}

//------------------------------------------------------------------------------------
/*  静的メソッド */


///*  モデルの座標取得 */
//FVector UMocapPluginGameInstance::GetRootPosition(const UMocapPluginGameInstance* instance, const int32 userId)
//{
//	if (instance == NULL || instance->MocapReceiver == NULL) {
//		return FVector::ZeroVector;
//	}
//
//	return instance->MocapReceiver->GetMocapPose(userId)->GetRootPosition();
//}
//
//
///**
//* 指定ボーンのFRotatorを取得
//*/
//FRotator UMocapPluginGameInstance::GetBoneRotator(const UMocapPluginGameInstance* instance, const EMocapBones::Type bone, const int32 userId)
//{
//	if (instance == NULL || instance->MocapReceiver == NULL) {
//		return FRotator::ZeroRotator;
//	}
//	return instance->MocapReceiver->GetMocapPose(userId)->BoneRotations[bone].Rotator();
//}
