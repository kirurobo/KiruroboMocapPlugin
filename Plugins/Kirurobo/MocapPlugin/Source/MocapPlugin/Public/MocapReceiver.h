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
	TMap<int32, UMocapPose*> PoseMap;

	/* PoseMap の中身を順不同で配列にしたもの。GCを防ぐためにこちらにも登録 */
	UPROPERTY()
		TArray<UMocapPose*> Poses;

	/* ユーザーIDを問わず最後に受信された姿勢 */
	UPROPERTY()
		UMocapPose *CurrentPose = nullptr;

	/* 空の姿勢 */
	UPROPERTY()
		UMocapPose *IdentityPose = nullptr;

	FPacketReader *packetReaderMvn;
	FPacketReader *packetReaderKinect;
	FPacketReader *packetReaderNeuron;

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


	/**
	* プロパティで指定されているポートで受信を開始します
	*/
	UFUNCTION(BlueprintCallable, Category = "Mocap")
		bool Connect();

	/**
	* 受信を終了します
	*/
	UFUNCTION(BlueprintCallable, Category = "Mocap")
		void Close();

	/**
	* 指定したユーザーIDについて現在の姿勢を取得します。
	* -1 を指定するとユーザーIDに関わらず最後に受信した姿勢を返します。
	*/
	UFUNCTION(BlueprintCallable, Category = "Mocap")
		UMocapPose* GetMocapPose(const int32 userId = -1);
};


