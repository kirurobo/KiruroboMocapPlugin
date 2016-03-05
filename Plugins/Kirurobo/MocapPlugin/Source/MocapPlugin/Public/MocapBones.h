// Copyright (c) 2015-2016 Kirurobo

#pragma once

#include "MocapBones.generated.h"

/**
* モーキャプ装置の分類
*/
UENUM(BlueprintType)
namespace EMocapDevices
{
	enum Type
	{
		None = 0,
		Mvn = 1,
		PerceptionNeuron = 2,
		Kinect = 3,
	};
}

/**
* このプラグインで保持する関節名と番号
*/
UENUM(BlueprintType)
namespace EMocapBones
{
	enum Type
	{
		Root = 0,
		Pelvis = 1,
		Spine01 = 2,
		Spine01L3 = 3,
		Spine02 = 4,
		Spine03 = 5,
		Neck = 6,
		Neck02 = 7,
		Head = 8,
		LeftThigh = 9,
		LeftThighTwist = 10,
		LeftCalf = 11,
		LeftCalfTwist = 12,
		LeftFoot = 13,
		LeftBall = 14,
		RightThigh = 15,
		RightThighTwist = 16,
		RightCalf = 17,
		RightCalfTwist = 18,
		RightFoot = 19,
		RightBall = 20,
		LeftClavicle = 21,
		LeftUpperArm = 22,
		LeftLowerArm = 23,
		LeftHand = 24,
		LeftLowerArmTwist = 25,
		LeftUpperArmTwist = 26,
		LeftThumb01 = 27,
		LeftThumb02 = 28,
		LeftThumb03 = 29,
		LeftInHandIndex = 30,
		LeftIndex01 = 31,
		LeftIndex02 = 32,
		LeftIndex03 = 33,
		LeftInHandMiddle = 34,
		LeftMiddle01 = 35,
		LeftMiddle02 = 36,
		LeftMiddle03 = 37,
		LeftInHandRing = 38,
		LeftRing01 = 39,
		LeftRing02 = 40,
		LeftRing03 = 41,
		LeftInHandPinky = 42,
		LeftPinky01 = 43,
		LeftPinky02 = 44,
		LeftPinky03 = 45,
		RightClavicle = 46,
		RightUpperArm = 47,
		RightLowerArm = 48,
		RightHand = 49,
		RightLowerArmTwist = 50,
		RightUpperArmTwist = 51,
		RightThumb01 = 52,
		RightThumb02 = 53,
		RightThumb03 = 54,
		RightInHandIndex = 55,
		RightIndex01 = 56,
		RightIndex02 = 57,
		RightIndex03 = 58,
		RightInHandMiddle = 59,
		RightMiddle01 = 60,
		RightMiddle02 = 61,
		RightMiddle03 = 62,
		RightInHandRing = 63,
		RightRing01 = 64,
		RightRing02 = 65,
		RightRing03 = 66,
		RightInHandPinky = 67,
		RightPinky01 = 68,
		RightPinky02 = 69,
		RightPinky03 = 70,
	};
}


/**
* MVN におけるボーン名
*/
UENUM(BlueprintType)
namespace EMocapMvnBones
{
	enum Type
	{
		Pelvis = 1,
		L5 = 2,
		L3 = 3,
		T12 = 4,
		T8 = 5,
		Neck = 6,
		Head = 8,
		LeftUpperLeg = 9,
		LeftLowerLeg = 11,
		LeftFoot = 13,
		LeftToe = 14,
		RightUpperLeg = 15,
		RightLowerLeg = 17,
		RightFoot = 19,
		RightToe = 20,
		LeftShoulder = 21,
		LeftUpperArm = 22,
		LeftForeArm = 23,
		LeftHand = 24,
		RightShoulder = 46,
		RightUpperArm = 47,
		RightForeArm = 48,
		RightHand = 49,

		None = 254,
	};
}

/**
* Neuron でのボーン名
*/
UENUM(BlueprintType)
namespace EMocapNeuronBones
{
	enum Type
	{
		Hips = 1,
		Spine = 2,
		Spine1 = 3,
		Spine2 = 4,
		Spine3 = 5,
		Neck = 6,
		Head = 8,
		LeftUpLeg = 9,
		LeftLeg = 11,
		LeftFoot = 13,
		RightUpLeg = 15,
		RightLeg = 17,
		RightFoot = 19,
		LeftShoulder = 21,
		LeftArm = 22,
		LeftForeArm = 23,
		LeftHand = 24,
		LeftHandThumb1 = 27,
		LeftHandThumb2 = 28,
		LeftHandThumb3 = 29,
		LeftInHandIndex = 30,
		LeftHandIndex1 = 31,
		LeftHandIndex2 = 32,
		LeftHandIndex3 = 33,
		LeftInHandMiddle = 34,
		LeftHandMiddle1 = 35,
		LeftHandMiddle2 = 36,
		LeftHandMiddle3 = 37,
		LeftInHandRing = 38,
		LeftHandRing1 = 39,
		LeftHandRing2 = 40,
		LeftHandRing3 = 41,
		LeftInHandPinky = 42,
		LeftHandPinky1 = 43,
		LeftHandPinky2 = 44,
		LeftHandPinky3 = 45,
		RightShoulder = 46,
		RightArm = 47,
		RightForeArm = 48,
		RightHand = 49,
		RightHandThumb1 = 52,
		RightHandThumb2 = 53,
		RightHandThumb3 = 54,
		RightInHandIndex = 55,
		RightHandIndex1 = 56,
		RightHandIndex2 = 57,
		RightHandIndex3 = 58,
		RightInHandMiddle = 59,
		RightHandMiddle1 = 60,
		RightHandMiddle2 = 61,
		RightHandMiddle3 = 62,
		RightInHandRing = 63,
		RightHandRing1 = 64,
		RightHandRing2 = 65,
		RightHandRing3 = 66,
		RightInHandPinky = 67,
		RightHandPinky1 = 68,
		RightHandPinky2 = 69,
		RightHandPinky3 = 70,

		None = 254,
	};
}

/**
* Kinect v2 でのボーン名
*/
UENUM(BlueprintType)
namespace EMocapKinectBones
{
	enum Type
	{
		SpineBase = 1,
		SpineMid = 4,
		SpineShoulder = 6,
		Neck = 7,
		Head = 8,
		HipLeft = 9,
		KneeLeft = 11,
		AnkleLeft = 13,
		FootLeft = 14,
		HipRight = 15,
		KneeRight = 17,
		AnkleRight = 19,
		FootRight = 20,
		ShoulderLeft = 21,
		ElbowLeft = 22,
		WristLeft = 23,
		HandLeft = 24,
		ThumbLeft = 27,
		HandTipLeft = 36,
		ShoulderRight = 46,
		ElbowRight = 47,
		WristRight = 48,
		HandRight = 49,
		ThumbRight = 52,
		HandTipRight = 61,

		None = 254,
	};
}

