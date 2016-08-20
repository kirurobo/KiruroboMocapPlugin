// Copyright (c) 2015-2016 Kirurobo

#include "MocapPluginPrivatePCH.h"
#include "MocapUdpSocket.h"


UMocapUdpSocket::UMocapUdpSocket( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	Initialize();
}

UMocapUdpSocket::~UMocapUdpSocket()
{
	this->Close();
}

// Sets default values
void UMocapUdpSocket::Initialize()
{
	//if (this->Device == EMocapDevices::Mvn) {
	//	this->m_Parser = new PacketParserMvn();
	//} else if (this->Device == EMocapDevices::PerceptionNeuron) {
	//	this->m_Parser = new PacketParserNeuron();
	//}
	////this->m_Parser->userIdOffset = this->userIdOffset;
}


/** 
* ポートを開く
*/
bool UMocapUdpSocket::Connect()
{
	if (m_Socket == NULL) {
		m_Socket = FUdpSocketBuilder(TEXT("Mocap UDP socket"))
			.BoundToPort(this->Port)
			.Build();
	}

	if (m_Socket != NULL) {
		/* UDP受信を開始 */
		m_Receiver = new FUdpSocketReceiver(m_Socket, FTimespan(0, 0, 1), TEXT("Mocap UDP receiver"));
		m_Receiver->OnDataReceived().BindUObject(this, &UMocapUdpSocket::UdpReceivedCallback);
		m_Receiver->Start();

		// 接続成功
		UE_LOG(LogTemp, Log, TEXT("MocapUdpSocket connected to port %d"), this->Port);
		return true;
	}

	// 接続失敗
	UE_LOG(LogTemp, Warning, TEXT("MocapUdpSocket could not open port %d"), this->Port);
	return false;
}

/**
*  受信を終了してポートを閉じる
*/
void UMocapUdpSocket::Close()
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

		UE_LOG(LogTemp, Log, TEXT("MocapUdpSocket closed port %d."), this->Port);
	}

	if (m_Parser != NULL) {
		delete m_Parser;
		m_Parser = NULL;
	}
}

/**
* 親となるReceiverを設定する
*/
void UMocapUdpSocket::SetParent(UMocapReceiver* parent)
{
	this->m_ParentReceiver = parent;
}

/*  UDPでデータが届いた際のコールバック */
void UMocapUdpSocket::UdpReceivedCallback(const FArrayReaderPtr& data, const FIPv4Endpoint&)
{
	//UE_LOG(LogTemp, Log, TEXT("MocapUdpSocket data received."));

	if (this->m_ParentReceiver) {
		const uint8* raw = data->GetData();
		this->m_ParentReceiver->Parse(raw, data->Num());
	}
	return;
}
