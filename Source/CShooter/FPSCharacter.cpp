// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimInstance.h"
#include "FPSAnimInstance.h"
#include "WeaponManager.h"
#include "UIManager.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup Weapon Manger
	WeaponManager = CreateDefaultSubobject<UWeaponManager>(TEXT("Weapon Manager"));
	//Setup UI Manager
	UIManager = CreateDefaultSubobject<UUIManager>(TEXT("UI Manager"));

	//Setup FPS Camera
	FirstPersonCam = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS Camera"));
	FirstPersonCam->SetupAttachment(GetCapsuleComponent());
	FirstPersonCam->RelativeLocation = FVector(0.0f, 0.0f, BaseEyeHeight + FPSCamHeight);
	bUseControllerRotationYaw = true;

	//Setup Mesh
	PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Player Mesh"));
	PlayerMesh->CastShadow = false;
	PlayerMesh->SetupAttachment(FirstPersonCam);
	PlayerMesh->RelativeLocation = FVector(0.0f, 0.0f, -80.0f);
	PlayerMesh->RelativeRotation= FRotator(0.0f, 0.0f, -90.0f);

	//Setup Gun Mesh
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	GunMesh->CastShadow = false;
	GunMesh->SetupAttachment(PlayerMesh, "WeaponPoint");


}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Get Player Character
	Player = GetWorld()->GetFirstPlayerController()->GetCharacter();

	//Get Anim BP
	Anim_BP = Cast<UFPSAnimInstance>(PlayerMesh->GetAnimInstance());
	if (Anim_BP != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Anim BP Found"));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Anim BP NULL"));
	}
	//UE_LOG(LogTemp, Warning, TEXT("Working"));
}


// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AnimationTick();
}

void AFPSCharacter::AnimationTick()
{
	APawn*Character = Anim_BP->TryGetPawnOwner();
	if (Character != NULL) {
		Anim_BP->inAir = Character->GetMovementComponent()->IsFalling();
		if (Character->GetVelocity().Size() > 0.0f) {
			Anim_BP->isMoving = true;
		}
		else {
			Anim_BP->isMoving = false;
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Null character"));
	}
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	PlayerInputComponent->BindAction("Run",IE_Pressed, this, &AFPSCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AFPSCharacter::RunEnd);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &AFPSCharacter::BeginPickup);
	PlayerInputComponent->BindAction("Pickup", IE_Released, this, &AFPSCharacter::EndPickup);

	//Equip Weapons
	PlayerInputComponent->BindAction("RifleEquip", IE_Pressed, this, &AFPSCharacter::EquipRifle);
	PlayerInputComponent->BindAction("ShotGunEquip", IE_Pressed, this, &AFPSCharacter::EquipShotGun);
	PlayerInputComponent->BindAction("GLEquip", IE_Pressed, this, &AFPSCharacter::EquipGL);
	PlayerInputComponent->BindAction("RPGEquip", IE_Pressed, this, &AFPSCharacter::EquipRPG);
	//PlayerInputComponent->BindAction("SniperEquip", IE_Pressed, this, &AFPSCharacter::EquipSniper);
	
	//Holister Weapons
	PlayerInputComponent->BindAction("UnequipWeapon", IE_Pressed, this, &AFPSCharacter::UnequipWeapon);
	PlayerInputComponent->BindAction("EquipWeaponsUp", IE_Pressed, this, &AFPSCharacter::CycleWeaponsUp);
	PlayerInputComponent->BindAction("EquipWeaponsDown", IE_Pressed, this, &AFPSCharacter::CycleWeaponsDown);
	
	//Fire weapon
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::FireWeapon);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFPSCharacter::FireWeaponRelease);

	//debug
	PlayerInputComponent->BindAction("Debug", IE_Pressed, this, &AFPSCharacter::Debug);
	
}

void AFPSCharacter::BeginPickup()
{
	bIsPickup = true;
}

void AFPSCharacter::EndPickup()
{
	bIsPickup = false;
}



void AFPSCharacter::MoveForward(float value)
{
	if (value != 0.0f) {
		AddMovementInput(GetActorForwardVector(), value);
		if (value < 0.0f) {
			bWalkingBackward = true;
		}
		else
		{
			bWalkingBackward = false;
		}
	}
}

void AFPSCharacter::MoveRight(float value)
{
	if (value != 0.0f) {
		AddMovementInput(GetActorRightVector(), value);
	}
}

void AFPSCharacter::Run()
{
	if (Anim_BP->isMoving) {
		if (Player != NULL&&bWalkingBackward==false) {
			Anim_BP->isRunning = true;
			Player->GetCharacterMovement()->MaxWalkSpeed = 800.0f;
			//UE_LOG(LogTemp, Error, TEXT("%f"), Anim_BP->TryGetPawnOwner()->GetVelocity().Size());
		}
		else {
			//UE_LOG(LogTemp, Error, TEXT("Null character"));
			Player->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		}
	}
	else {
		Anim_BP->isRunning = false;
	}
		
}

void AFPSCharacter::RunEnd()
{
	Anim_BP->isRunning = false;
	Player->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	
}


void AFPSCharacter::EquipRifle()
{
	if (WeaponManager->Rifle!=NULL&&isRifle==false) {
		isRifle = true;
		isGL = false;
		isRPG = false;
		isShotgun = false;
		isSniper = false;
		Anim_BP->PlaySlotAnimationAsDynamicMontage(EquipAnimation, "UpperBody", 0.0f);
		Anim_BP->isWeaponEquipped = true;
		GunMesh->SetSkeletalMesh(WeaponManager->Rifle->PickupMesh->SkeletalMesh);
		UE_LOG(LogTemp, Error, TEXT("Rifle"));
		EquipedWeapon = EWeaponType::T_Rifle;
	}
	if (WeaponManager->Rifle == NULL) {
		UE_LOG(LogTemp, Error, TEXT("Rifle NULL"));
	}

}

void AFPSCharacter::EquipShotGun()
{
	if (WeaponManager->ShotGun != NULL && isShotgun == false) {
		isShotgun = true;
		isGL = false;
		isRPG = false;
		isRifle = false;
		isSniper = false;
		Anim_BP->PlaySlotAnimationAsDynamicMontage(EquipAnimation, "UpperBody", 0.0f);
		Anim_BP->isWeaponEquipped = true;
		GunMesh->SetSkeletalMesh(WeaponManager->ShotGun->PickupMesh->SkeletalMesh);
		UE_LOG(LogTemp, Error, TEXT("Shot"));
		EquipedWeapon = EWeaponType::T_ShotGun;
	}

	if (WeaponManager->ShotGun == NULL) {
		UE_LOG(LogTemp, Error, TEXT("shotgun NULL"));
	}
}

void AFPSCharacter::EquipGL()
{
	if (WeaponManager->GL != NULL && isGL == false) {
		isGL = true;
		isShotgun = false;
		isRPG = false;
		isRifle = false;
		isSniper = false;
		Anim_BP->PlaySlotAnimationAsDynamicMontage(EquipAnimation, "UpperBody", 0.0f);
		Anim_BP->isWeaponEquipped = true;
		GunMesh->SetSkeletalMesh(WeaponManager->GL->PickupMesh->SkeletalMesh);
		UE_LOG(LogTemp, Error, TEXT("GL"));
		EquipedWeapon = EWeaponType::T_GL;
	}

	if (WeaponManager->GL == NULL) {
		UE_LOG(LogTemp, Error, TEXT("GL NULL"));
	}
}

void AFPSCharacter::EquipRPG()
{
	if (WeaponManager->RPG != NULL && isRPG == false) {
		isRPG = true;
		isShotgun = false;
		isGL = false;
		isRifle = false;
		isSniper = false;
		Anim_BP->PlaySlotAnimationAsDynamicMontage(EquipAnimation, "UpperBody", 0.0f);
		Anim_BP->isWeaponEquipped = true;
		GunMesh->SetSkeletalMesh(WeaponManager->RPG->PickupMesh->SkeletalMesh);
		UE_LOG(LogTemp, Error, TEXT("RPG"));
		EquipedWeapon = EWeaponType::T_RPG;
	}

	if (WeaponManager->RPG == NULL) {
		UE_LOG(LogTemp, Error, TEXT("RPG NULL"));
	}
}

void AFPSCharacter::EquipSniper()
{
	if (WeaponManager->Sniper != NULL && isSniper == false) {
		isRPG = false;
		isShotgun = false;
		isGL = false;
		isRifle = false;
		isSniper = true;
		Anim_BP->PlaySlotAnimationAsDynamicMontage(EquipAnimation, "UpperBody", 0.0f);
		Anim_BP->isWeaponEquipped = true;
		GunMesh->SetSkeletalMesh(WeaponManager->Sniper->PickupMesh->SkeletalMesh);
		UE_LOG(LogTemp, Error, TEXT("Sniper"));
	}

	if (WeaponManager->Sniper == NULL) {
		UE_LOG(LogTemp, Error, TEXT("SniperNULL"));
	}
}

void AFPSCharacter::UnequipWeapon()
{
	if (Anim_BP->isWeaponEquipped == true) {
		Anim_BP->PlaySlotAnimationAsDynamicMontage(UnequipAnimation, "UpperBody", 0.0f);
		Anim_BP->isWeaponEquipped = false;
		isRifle = false;
		isGL = false;
		isRPG = false;
		isShotgun = false;
		isSniper = false;
		EquipedWeapon = EWeaponType::T_None;
	}
	
}

void AFPSCharacter::CycleWeaponsUp()
{
	WeaponIndex++;
	int32 clampVal= FMath::Clamp(WeaponIndex, 0, 8);
	//UE_LOG(LogTemp, Error, TEXT("index%d"), clampVal);
	WeaponIndex = clampVal;
	SwitchWeapon(clampVal);
}

void AFPSCharacter::CycleWeaponsDown()
{
	WeaponIndex--;
	int32 clampVal = FMath::Clamp(WeaponIndex, 0, 8);
	UE_LOG(LogTemp, Error, TEXT("index%d"), clampVal);
	WeaponIndex = clampVal;
	SwitchWeapon(clampVal);
}

void AFPSCharacter::FireWeapon()
{
	if (Anim_BP->isWeaponEquipped == true) {
		WeaponManager->FireWeaponStart(EquipedWeapon);
	}
}

void AFPSCharacter::FireWeaponRelease()
{
	if (Anim_BP->isWeaponEquipped == true) {
		WeaponManager->FireWeaponEnd();
	}
}

void AFPSCharacter::SwitchWeapon(int32 Index)
{
	switch(Index) {
	case 0:
	{
		EquipRifle();
		break;
	}
	case 2:
	{
		EquipShotGun();
		break;
	}
	case 4:
	{
		EquipGL();
		break;
	}
	case 6:
	{
		EquipRPG();
		break;
	}
	case 8:
	{
		//EquipSniper();
		break;
	}
	}
}


void AFPSCharacter::HideWeaponUnequip()
{
	GunMesh->SetSkeletalMesh(NULL);
}


void AFPSCharacter::Debug()
{
	
	UE_LOG(LogTemp, Error, TEXT("index%s"));
}

