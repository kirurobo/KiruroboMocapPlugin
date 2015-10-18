// Copyright (c) 2015 Kirurobo

#pragma once

#include "MocapBones.h"
#include "MocapPose.h"
#include "PacketReaderMvn.h"
#include "PacketReaderKinect.h"
#include "PacketReaderNeuron.h"
#include "MocapReceiver.generated.h"


/**
 * UDP receiver base class
 */
UCLASS(ClassGroup = MocapPlugin)
class UMocapReceiver : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	virtual ~UMocapReceiver();

protected:
	FSocket *m_Socket;
	FUdpSocketReceiver *m_Receiver;
	FRunnableThread *m_Thread;

	/* モーキャプのデータをユーザーID毎に保存するコンテナ */
	TMap<int32, UMocapPose*> Poses;

	/* ユーザーIDを問わず最後に受信された姿勢 */
	UMocapPose *CurrentPose = nullptr;

	/* 空の姿勢 */
	UMocapPose *IdentityPose = nullptr;

	UPacketReader *packetReaderMvn;
	UPacketReader *packetReaderKinect;
	UPacketReader *packetReaderNeuron;

	virtual void Initialize();

	/*  UDP受信時のコールバック */
	void UdpReceivedCallback(const FArrayReaderPtr& data, const FIPv4Endpoint& ip);

public:
	/**
	* UDPのポート番号
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		int32 Port = 7001;	// 9763;

	/**
	* MVN から受信したユーザーIDにこの値を加えたものを、IDとして扱う
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		int32 MvnUserIdOffset = 0;

	/**
	* Axis Neuron から受信したユーザーIDにこの値を加えたものを、IDとして扱う
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		int32 NeuronUserIdOffset = 0;

	/**
	* Kinect から受信したユーザーIDにこの値を加えたものを、IDとして扱う
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		int32 KinectUserIdOffset = 0;



	UFUNCTION(BlueprintCallable, Category = "Mocap")
		bool Connect();

	UFUNCTION(BlueprintCallable, Category = "Mocap")
		void Close();

	UFUNCTION(BlueprintCallable, Category = "Mocap")
		UMocapPose* GetMocapPose(const int32 userId = -1);
};


