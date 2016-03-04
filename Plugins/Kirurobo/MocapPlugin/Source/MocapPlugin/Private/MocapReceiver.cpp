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
		m_Socket = FUdpSocketBuilder(TEXT("Mocap UDP socket"))
			.BoundToPort(this->Port)
			.Build();
	}

	if (m_Socket != NULL) {
		const bool bAutoDeleteSelf = true;
		const bool bAutoDeleteRunnable = true;

		/* 受信されたデータの保存領域 */
		CurrentPose = NewObject<UMocapPose>();

		/*  パケット解釈部 */
		packetParserMvn = new PacketParserMvn();
		//packetParserKinect = new PacketParserKinect();
		packetParserNeuron = new PacketParserNeuron();

		/* UDP受信を開始 */
		m_Receiver = new FUdpSocketReceiver(m_Socket, FTimespan(0, 0, 1), TEXT("Mocap UDP receiver"));
		m_Receiver->OnDataReceived().BindUObject(this, &UMocapReceiver::UdpReceivedCallback);

		// 接続成功
		UE_LOG(LogTemp, Log, TEXT("Connected to UDP port %d"), this->Port);

		return true;
	}

	// 接続失敗
	UE_LOG(LogTemp, Warning, TEXT("Could not open UDP port %d"), this->Port);
	return false;
}

/*  受信を終了してポートを閉じる */
/* 	End Play イベントで呼ぶこと。 */
void UMocapReceiver::Close()
{
	if (m_Receiver != NULL) {
		m_Receiver->Exit();
		delete m_Receiver;
		m_Receiver = NULL;
	}

	if (m_Socket != NULL) {
		m_Socket->Close();
		delete m_Socket;
		m_Socket = NULL;

		UE_LOG(LogInit, Log, TEXT("MocapReceiver closed port %d."), this->Port);
	}

	if (packetParserMvn != NULL) {
		delete (PacketParserMvn*) packetParserMvn;
		packetParserMvn = NULL;
	}
	if (packetParserNeuron != NULL) {
		delete (PacketParserNeuron*) packetParserNeuron;
		packetParserNeuron = NULL;
	}
}

/*  UDPでデータが届いた際のコールバック */
void UMocapReceiver::UdpReceivedCallback(const FArrayReaderPtr& data, const FIPv4Endpoint&)
{
	bool received = false;
	
	/* モーキャプソフト毎にその形式か調べて受信する */
	if (packetParserMvn->Read(data, this->CurrentPose)) {
		received = true;
		this->CurrentPose->UserId += this->MvnUserIdOffset;
	} else if (packetParserNeuron->Read(data, this->CurrentPose)) {
		received = true;
		this->CurrentPose->UserId += this->NeuronUserIdOffset;
	}

	/* 受信できたらユーザーID毎に保存する */
	if (received) {
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
	}
}

/* 指定されたユーザーIDの姿勢を返す */
UMocapPose* UMocapReceiver::GetMocapPose(const int32 userId)
{
	if (!this->m_Socket) return this->IdentityPose;
	if (userId < 0) return this->CurrentPose;
	UMocapPose** pPose =  this->PoseMap.Find(userId);
	if (pPose == nullptr) {
		return this->IdentityPose;
	}
	else {
		return *pPose;
	}
}
