// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterPickup.generated.h"

class USphereComponent;
class UWidgetComponent;
class USceneComponent;
class UAnimMontage;
class AFPSCharacter;
class UPrimitiveComponent;
class UTexture2D;
class USoundWave;
class USkeletalMeshComponent;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	T_None				UMETA(DisplayName = "None"),
	T_Rifle				UMETA(DisplayName = "Rifle"),
	T_RPG				UMETA(DisplayName = "RPG"),
	T_ShotGun           UMETA(DisplayName = "ShotGun"),
	T_GL				UMETA(DisplayName = "Grande Launcher"),
	T_Sniper			UMETA(DisplayName = "Sniper")
};


UCLASS()
class CSHOOTER_API AMasterPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterPickup();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pick Up Object Attributes")
	USkeletalMeshComponent*PickupMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pick Up Object Attributes")
	UWidgetComponent*PickupWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pick Up Object Attributes")
	USphereComponent*SphereCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Protertise")
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Protertise")
	AActor *WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Protertise")
	int32 ClipSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Protertise")
	int32 CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Protertise")
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Protertise")
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Protertise")
	UTexture2D*WeaponImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Protertise")
	UAnimMontage*FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Protertise")
	UAnimMontage*ReloadAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Protertise")
	USoundWave*FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Protertise")
	USoundWave*ReloadSound;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	USceneComponent*DefaultScenceComp;
	bool bCanPickUp = false;
	AFPSCharacter*PlayerCharacter = NULL;
	void GetCharacter(AActor*Player);
	void RemoveWeaponWorld();

};
