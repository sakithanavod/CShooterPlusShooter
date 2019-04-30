// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MasterPickup.h"
#include "FPSCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class UAnimInstance;
class UFPSAnimInstance;
class UWeaponManager;
class UUIManager;
class UAnimMontage;
class UAnimSequenceBase;


UCLASS()
class CSHOOTER_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPSAttributes")
	float FPSCamHeight = 5.0f;
	bool bIsPickup = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Manager Stats")
	UWeaponManager*WeaponManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Manager Stats")
	UUIManager*UIManager;

	EWeaponType EquipedWeapon;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent*FirstPersonCam;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerMesh")
	USkeletalMeshComponent*PlayerMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GunMesh")
	USkeletalMeshComponent*GunMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnimMonatges")
	UAnimSequenceBase* EquipAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAnimMonatges")
	UAnimSequenceBase* UnequipAnimation;

	void BeginPickup();
	void EndPickup();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AnimationTick();
	void HideWeaponUnequip();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	void MoveForward(float value);
	void MoveRight(float value);
	void Run();
	void RunEnd();
	void SwitchWeapon(int32 Index);

	//weapon equip functions
	void EquipRifle();
	void EquipShotGun();
	void EquipGL();
	void EquipRPG();
	void EquipSniper();
	void UnequipWeapon();
	void CycleWeaponsUp();
	void CycleWeaponsDown();
	void FireWeapon();
	void FireWeaponRelease();
	//debug
	void Debug();

private:
	int32 WeaponIndex = 0;
	bool isRifle = false;
	bool isShotgun = false;
	bool isGL = false;
	bool isRPG = false;
	bool isSniper = false;
	bool bWalkingBackward = false;
	bool bIsFiring = false;
	UFPSAnimInstance*Anim_BP;
	ACharacter*Player;
};
