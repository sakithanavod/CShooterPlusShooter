// Fill out your copyright notice in the Description page of Project Settings.

#include "UnequipNotify.h"
//#include "Engine/Engine.h"
#include "Components/SkeletalMeshComponent.h"
#include "FPSAnimInstance.h"
#include "FPSCharacter.h"

void UUnequipNotify::Notify(USkeletalMeshComponent*MeshComp, UAnimSequenceBase*Animation) {
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, __FUNCTION__);
	
	UFPSAnimInstance*AnimBP = Cast<UFPSAnimInstance>(MeshComp->GetAnimInstance());
	AFPSCharacter*Player = Cast<AFPSCharacter>(AnimBP->TryGetPawnOwner());

	Player->HideWeaponUnequip();
}