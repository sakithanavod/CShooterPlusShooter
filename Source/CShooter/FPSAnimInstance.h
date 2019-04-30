// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Animation/AnimInstance.h"
#include "CoreMinimal.h"
#include "FPSAnimInstance.generated.h"



/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance,BlueprintType)
class CSHOOTER_API UFPSAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	UFPSAnimInstance(const FObjectInitializer&ObjectInitializer);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inherited Variables")
	bool inAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inherited Variables")
	bool isMoving;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inherited Variables")
	bool isRunning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inherited Variables")
	bool isWeaponEquipped;
};
