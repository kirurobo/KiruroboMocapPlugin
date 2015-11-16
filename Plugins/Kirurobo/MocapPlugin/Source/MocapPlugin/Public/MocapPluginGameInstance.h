// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "MocapReceiver.h"
#include "MocapPluginGameInstance.generated.h"


UCLASS(ClassGroup = MocapPlugin)
class UMocapPluginGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;
	virtual void Shutdown() override;

public:

	/**
	* UDPの受信ポート
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		int32 PortNo = 7001;		// 9763;	// Neuron:7001, MVN:9763

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
	bool MultiUsers = false;

	/**
	* MVN から受信したユーザーIDにこの値を加えたものを、IDとして扱う
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		int32 MvnUserIdOffset = 100;

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
		bool Connect(int32 port = -1);

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