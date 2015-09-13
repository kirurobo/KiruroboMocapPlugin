// Copyright (c) 2015 Kirurobo

#pragma once

#include "MocapBones.h"
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

	FSocket *m_Socket;
	FUdpSocketReceiver *m_Receiver;
	FRunnableThread *m_Thread;

	int8 BONE_NUMBER = 0;

	TArray<uint8> parentSegments;
	TArray<FQuat> lastRotations;

	UPacketReader *packetReaderMvn;
	UPacketReader *packetReaderKinect;
	UPacketReader *packetReaderNeuron;

	virtual void Initialize();

	/*  UDP受信時のコールバック */
	void UdpReceivedCallback(const FArrayReaderPtr& data, const FIPv4Endpoint& ip);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		int32 Port = 9763;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mocap")
		bool MultiUsers = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mocap")
		TArray<FQuat> BoneRotations;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mocap")
		FVector RootPosition;

	UFUNCTION(BlueprintCallable, Category = "Mocap")
		bool Connect();

	UFUNCTION(BlueprintCallable, Category = "Mocap")
		void Close();
};


