// Copyright (c) 2015 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "MocapReceiver.h"
#include "Runtime/Launch/Resources/Version.h"


UMocapReceiver::UMocapReceiver( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	Initialize();
}

UMocapReceiver::~UMocapReceiver()
{
}

// Sets default values
void UMocapReceiver::Initialize()
{
	this->IdentityPose = NewObject<UMocapPose>();
}


/*  ポートに接続 */
//
/*  Begin Play イベントで呼ぶこと。 */
bool UMocapReceiver::Connect()
{
	if (m_Socket == NULL) {
		UE_LOG(LogInit, Warning, TEXT("Initialize UDP socket %d..."), this->Port);
		m_Socket = FUdpSocketBuilder(TEXT("Mocap UDP socket"))
			.AsNonBlocking()
			.AsReusable()
			.BoundToPort(this->Port)
			.Build();
	}

	if (m_Socket != NULL) {
		const bool bAutoDeleteSelf = true;
		const bool bAutoDeleteRunnable = true;

		/* 受信されたデータの保存領域 */
		CurrentPose = NewObject<UMocapPose>();

		/*  パケット解釈部 */
		packetReaderMvn = new FPacketReaderMvn();
		//packetReaderKinect = new FPacketReaderKinect();
		packetReaderNeuron = new FPacketReaderNeuron();

		/* UDP受信を開始 */
		UE_LOG(LogInit, Warning, TEXT("Start UDP receiver."));
		m_Receiver = new FUdpSocketReceiver(
			m_Socket,
			FTimespan::FromMilliseconds(100),
			TEXT("Mocap UDP receiver")
		);
		m_Receiver->OnDataReceived().BindUObject(this, &UMocapReceiver::UdpReceivedCallback);
#if (ENGINE_MAJOR_VERSION >= 4) && (ENGINE_MINOR_VERSION >= 11)
		m_Receiver->Start();
#endif
		return true;
	}
	return false;
}

/*  受信を終了してポートを閉じる */
/* 	End Play イベントで呼ぶこと。 */
void UMocapReceiver::Close()
{
	UE_LOG(LogInit, Warning, TEXT("Close UDP receiver."));

	if (m_Receiver != NULL) {
		m_Receiver->Exit();
		delete m_Receiver;
		m_Receiver = NULL;
	}

	if (m_Socket != NULL) {
		m_Socket->Close();
		delete m_Socket;
		m_Socket = NULL;
	}
	if (packetReaderMvn != NULL) {
		delete (FPacketReaderMvn*)packetReaderMvn;
		packetReaderMvn = NULL;
	}
	if (packetReaderNeuron != NULL) {
		delete (FPacketReaderNeuron*)packetReaderNeuron;
		packetReaderNeuron = NULL;
	}
}

/*  UDPでデータが届いた際のコールバック */
void UMocapReceiver::UdpReceivedCallback(const FArrayReaderPtr& data, const FIPv4Endpoint&)
{
	bool received = false;

	//UE_LOG(LogInit, Warning, TEXT("UDP packet reached."));

	/* モーキャプソフト毎にその形式か調べて受信する */
	if (packetReaderMvn->Read(data, this->CurrentPose)) {
		received = true;
		this->CurrentPose->UserId += this->MvnUserIdOffset;
	} else if (packetReaderNeuron->Read(data, this->CurrentPose)) {
		received = true;
		this->CurrentPose->UserId += this->NeuronUserIdOffset;
	}

	/* 受信できたらユーザーID毎に保存する */
	if (received) {
		int userId = this->CurrentPose->UserId;

		//UE_LOG(LogInit, Warning, TEXT("User ID: %d"), userId);

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
	}
}

/* 指定されたユーザーIDの姿勢を返す */
UMocapPose* UMocapReceiver::GetMocapPose(const int32 userId)
{
	if (userId < 0) return this->CurrentPose;
	UMocapPose** pPose =  this->PoseMap.Find(userId);
	if (pPose == nullptr) {
		return this->IdentityPose;
	}
	else {
		return *pPose;
	}
}
