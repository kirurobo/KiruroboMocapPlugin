// Copyright (c) 2015-2016 Kirurobo

#pragma once

#include "Object.h"
#include "Sockets.h"
#include "MocapBones.h"
#include "MocapPose.h"
#include "MocapUdpSocket.h"
#include "PacketParserMvn.h"
#include "PacketParserNeuron.h"
#include "PacketParserKinect.h"
#include "MocapReceiver.generated.h"


/**
 * UDP receiver base class
 */
UCLASS(ClassGroup = "MocapPlugin")
class UMocapReceiver : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	virtual ~UMocapReceiver();

	/**
	* プロパティで指定されているポートで受信を開始します
	*/
	bool Parse(const uint8* data, const int32 length);

protected:
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

	/* パケット解析の担当 */
	PacketParser* Parsers[3];

	virtual void Initialize();

public:
	/**
	* TCP または UDP のソケット
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		TArray<UMocapUdpSocket*> Sockets;

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


