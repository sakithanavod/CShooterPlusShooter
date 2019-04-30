// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"




// Sets default values for this component's properties
UWeaponManager::UWeaponManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UWeaponManager::BeginPlay()
{
	Super::BeginPlay();
	TimerDelFire.BindUFunction(this, FName("StartFire"));
	// ...

}


// Called every frame
void UWeaponManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponManager::AddtoInventory(AMasterPickup * Weapon)
{
	switch (Weapon->WeaponType)
	{
	case EWeaponType::T_Rifle:
		//WeaponInventory.Insert(Weapon, 0);
		UE_LOG(LogTemp, Warning, TEXT("Rifle"));
		Rifle = Weapon;
		break;
	case EWeaponType::T_ShotGun:
		//WeaponInventory.Insert(Weapon, 1);
		UE_LOG(LogTemp, Warning, TEXT("Shot"));
		ShotGun = Weapon;
		break;
	case EWeaponType::T_GL:
		//WeaponInventory.Insert(Weapon, 2);
		UE_LOG(LogTemp, Warning, TEXT("GL"));
		GL = Weapon;
		break;
	case EWeaponType::T_RPG:
		//WeaponInventory.Insert(Weapon, 3);
		UE_LOG(LogTemp, Warning, TEXT("RPG"));
		RPG = Weapon;
		break;
	case EWeaponType::T_Sniper:
		//WeaponInventory.Insert(Weapon, 3);
		UE_LOG(LogTemp, Warning, TEXT("Sniper"));
		Sniper = Weapon;
		break;
	default:
		break;
	}
}

void UWeaponManager::FireWeaponStart(EWeaponType EquipedWeapon)
{
	SetUpWeaponAttr(EquipedWeapon);
}

void UWeaponManager::FireWeaponEnd()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void UWeaponManager::StartFire()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	FVector FireEndLocation = PlayerLocation + PlayerRotation.Vector()*FireDistance;
	DrawDebugLine(GetWorld(), PlayerLocation, FireEndLocation, FColor::Red, true, 3.0f);
}

void UWeaponManager::SetUpWeaponAttr(EWeaponType EqWeapon)
{
	switch (EqWeapon)
	{
	case EWeaponType::T_Rifle:
		RifleFunction();
		break;
	case EWeaponType::T_ShotGun:
		ShotGunFunction();
		break;
	case EWeaponType::T_GL:
		GLFunction();
		break;
	case EWeaponType::T_RPG:
		RPGFunction();
		break;
	case EWeaponType::T_None:
		break;
	default:
		break;
	}
}

void UWeaponManager::RifleFunction()
{
	FireDistance = 15000.0f;
	FireRate = 0.1f;
	GetWorld()->GetTimerManager().SetTimer(TimerHandleFire, TimerDelFire, FireRate, true);
	//StartFire();

}

void UWeaponManager::ShotGunFunction()
{
}

void UWeaponManager::GLFunction()
{
}

void UWeaponManager::RPGFunction()
{
}


