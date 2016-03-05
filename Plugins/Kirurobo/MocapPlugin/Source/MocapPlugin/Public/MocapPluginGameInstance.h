// Copyright (c) 2015-2016 Kirurobo

#pragma once

#include "Engine/GameInstance.h"
#include "MocapReceiver.h"
#include "MocapPluginGameInstance.generated.h"

/**
* 起動時から最後まで受信クラスを保持するためGameInstanceに処理を含める
*/
UCLASS(ClassGroup = "MocapPlugin")
class UMocapPluginGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;
	virtual void Shutdown() override;

public:

	/**
	* ソケット
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		TArray<UMocapUdpSocket*> Sockets;	// Neuron:7001, MVN:9763

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
	* 実際にUDP受信を取り扱うクラス
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mocap")
		UMocapReceiver *MocapReceiver;


	/**
	* 接続を開始します。既に接続中の場合は一旦切断されます。
	*/
	UFUNCTION(BlueprintCallable, Category = "Mocap")
		bool Connect();

	/**
	* 接続を終了します
	*/
	UFUNCTION(BlueprintCallable, Category = "Mocap")
		void Close();


	/*  基準座標を取得します */
	UFUNCTION(BlueprintCallable, Category = "Mocap")
		const FVector GetRootPosition(const int32 userId = -1);

	/**
	* モーキャプで受信されたボーンの姿勢を取得します。
	* 各姿勢は親ボーンに対する相対姿勢です。
	*/
	UFUNCTION(BlueprintCallable, Category = "Mocap")
		const FRotator GetBoneRotator(const EMocapBones::Type bone, const int32 userId = -1);


	///*  基準座標を取得します */
	//UFUNCTION(BlueprintCallable, Category = "Mocap")
	//	static FVector GetRootPosition(const UMocapPluginGameInstance* instance, const int32 userId = -1);

	///**
	//* モーキャプで受信されたボーンの姿勢を取得します。
	//* 各姿勢は親ボーンに対する相対姿勢です。
	//*/
	//UFUNCTION(BlueprintCallable, Category = "Mocap")
	//	static FRotator GetBoneRotator(const UMocapPluginGameInstance* instance, const EMocapBones::Type bone, const int32 userId = -1);
};