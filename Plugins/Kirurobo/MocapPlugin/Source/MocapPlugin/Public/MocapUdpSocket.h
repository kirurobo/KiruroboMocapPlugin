// Copyright (c) 2015-2016 Kirurobo

#pragma once

#include "Object.h"
#include "Networking.h"
#include "MocapBones.h"
#include "PacketParserMvn.h"
#include "PacketParserNeuron.h"
#include "PacketParserKinect.h"
#include "MocapUdpSocket.generated.h"

/**
* 指定ポートについてUDPの受信を行う
*/
UCLASS(ClassGroup = "MocapPlugin")
class UMocapUdpSocket : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	virtual ~UMocapUdpSocket();

protected:
	FSocket *m_Socket;
	FUdpSocketReceiver *m_Receiver;
	FRunnableThread *m_Thread;
	
	PacketParser* m_Parser;

	UMocapReceiver* m_ParentReceiver;	/* 親となっているReceiver */

	/*  UDP受信時のコールバック */
	void UdpReceivedCallback(const FArrayReaderPtr& data, const FIPv4Endpoint& ip);

	void Initialize();

public:
	/**
	* UDPのポート番号
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		int32 Port = 7001;	// 9763;
	
	/**
	* UDPのポート番号
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		FName Ip = TEXT("");
	
	/**
	* 相手先装置
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		TEnumAsByte<EMocapDevices::Type> Device = EMocapDevices::None;
	
	/**
	* プロパティで指定されているポートで受信を開始します
	*/
	UFUNCTION(Category = "Mocap")
		bool Connect();

	/**
	* 受信を終了します
	*/
	UFUNCTION(Category = "Mocap")
		void Close();

	/**
	* 親を設定します
	*/
	UFUNCTION(Category = "Mocap")
		void SetParent(UMocapReceiver* parent);

	DECLARE_EVENT_ThreeParams(FReceivedDelegate, FReceivedEvent, const uint8*, PacketParser*, UMocapPose*)
	
	FReceivedEvent OnReceived;
};
