// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAnimInstance.h"


UFPSAnimInstance::UFPSAnimInstance(const FObjectInitializer&ObjectInitializer) :Super(ObjectInitializer) {
	inAir = false;
	isRunning = false;
	isMoving = false;
	isWeaponEquipped = false;
}