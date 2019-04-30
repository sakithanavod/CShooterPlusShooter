// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MasterPickup.h"
#include "TimerManager.h"
#include "Components/ActorComponent.h"
#include "WeaponManager.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CSHOOTER_API UWeaponManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponManager();


	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Slots")
	TArray<AMasterPickup*> WeaponInventory;*/
	AMasterPickup*Rifle = NULL;
	AMasterPickup*ShotGun = NULL;
	AMasterPickup*GL = NULL;
	AMasterPickup*RPG = NULL;
	AMasterPickup*Sniper = NULL;

	AMasterPickup*EquippedWeapon = NULL;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AddtoInventory(AMasterPickup*Weapon);
	void FireWeaponStart(EWeaponType EquipedWeapon);
	void FireWeaponEnd();

private:	
	FVector PlayerLocation;
	FRotator PlayerRotation;
	FTimerDelegate TimerDelFire;
	FTimerHandle TimerHandleFire;

	//functions
	UFUNCTION()
	void StartFire();
	void SetUpWeaponAttr(EWeaponType EqWeapon);

	//weapon functions
	void RifleFunction();
	void ShotGunFunction();
	void GLFunction();
	void RPGFunction();

	//Weapon Attributes
	float FireDistance = 15000.0f;
	float FireRate = 0.1f;
};
