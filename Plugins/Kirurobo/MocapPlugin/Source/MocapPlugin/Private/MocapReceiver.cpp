// Copyright (c) 2015 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "MocapReceiver.h"


UMocapReceiver::UMocapReceiver( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	Initialize();
}


// Sets default values
void UMocapReceiver::Initialize()
{
	UEnum* pBones = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMocapBones"), true);
	BONE_NUMBER = pBones->NumEnums();

	/*  値を保持する配列を準備 */
	BoneRotations.Reserve(BONE_NUMBER);
	for (int i = 0; i < BONE_NUMBER; i++) {
		BoneRotations.Add(FQuat(0, 0, 0, 1));
	}
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

		m_Receiver = new FUdpSocketReceiver(m_Socket, FTimespan(0, 0, 1), TEXT("Mocap UDP receiver"));
		m_Receiver->OnDataReceived().BindUObject(this, &UMocapReceiver::UdpReceivedCallback);

		/*  パケット解釈部 */
		packetReaderMvn = new UPacketReaderMvn();
		//packetReaderKinect = new UPacketReaderKinect();
		packetReaderNeuron = new UPacketReaderNeuron();

		this->BoneRotations = packetReaderMvn->BoneRotations;
		this->RootPosition = packetReaderMvn->RootPosition;
		return true;
	}
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
	}
	if (packetReaderMvn != NULL) {
		delete packetReaderMvn;
		packetReaderMvn = NULL;
	}
	if (packetReaderNeuron != NULL) {
		delete packetReaderNeuron;
		packetReaderNeuron = NULL;
	}
}

/*  UDPでデータが届いた際のコールバック */
void UMocapReceiver::UdpReceivedCallback(const FArrayReaderPtr& data, const FIPv4Endpoint&)
{
	if (packetReaderMvn->Read(data)) {
		this->RootPosition = packetReaderMvn->RootPosition;
		this->BoneRotations = packetReaderMvn->BoneRotations;
	} else if (packetReaderNeuron->Read(data)) {
		this->RootPosition = packetReaderNeuron->RootPosition;
		this->BoneRotations = packetReaderNeuron->BoneRotations;
	}
}
