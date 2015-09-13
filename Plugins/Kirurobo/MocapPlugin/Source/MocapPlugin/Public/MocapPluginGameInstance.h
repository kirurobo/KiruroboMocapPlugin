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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		int32 PortNo = 9763;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		bool MultiUsers = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		UMocapReceiver *MocapReceiver;


	UFUNCTION(BlueprintCallable, Category = "Mocap")
		bool Connect(int32 port = -1);

	UFUNCTION(BlueprintCallable, Category = "Mocap")
		void Close();


	/*  基準となる座標を取得 */
	UFUNCTION(BlueprintCallable, Category = "Mocap")
		static FVector GetRootPosition(const int32 userId, const UMocapPluginGameInstance* instance);
};