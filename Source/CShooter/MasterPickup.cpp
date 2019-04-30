// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterPickup.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/Engine.h"
#include "FPSCharacter.h"
#include "WeaponManager.h"

// Sets default values
AMasterPickup::AMasterPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultScenceComp = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneCompoenent"));

	PickupMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(DefaultScenceComp);
	
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereColider"));
	SphereCollider->SetupAttachment(PickupMesh);


	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetPickup"));
	PickupWidget->SetupAttachment(PickupMesh);

	//bind overlap events
	SphereCollider->OnComponentBeginOverlap.__Internal_AddDynamic(this, &AMasterPickup::OnOverlap, "OnOverlap");
}

// Called when the game starts or when spawned
void AMasterPickup::BeginPlay()
{
	Super::BeginPlay();
	SphereCollider->SetGenerateOverlapEvents(true);
	SphereCollider->OnComponentEndOverlap.__Internal_AddDynamic(this, &AMasterPickup::OnOverlapEnd, "OnOverlapEnd");

}

// Called every frame
void AMasterPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerCharacter != NULL) {
		if ((PlayerCharacter->bIsPickup)&&bCanPickUp) {
			GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::Blue, FString::Printf(TEXT("NO")));
			RemoveWeaponWorld();
		}

	}
}

void AMasterPickup::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GetCharacter(OtherActor);
	bCanPickUp = true;
}

void AMasterPickup::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//PlayerCharacter = NULL;
	bCanPickUp = false;
}

void AMasterPickup::GetCharacter(AActor * Player)
{
	PlayerCharacter = Cast<AFPSCharacter>(Player);
}

void AMasterPickup::RemoveWeaponWorld()
{
	if (this) {
		this->SetActorHiddenInGame(true);
		SphereCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		if (PlayerCharacter != NULL) {
			PlayerCharacter->WeaponManager->AddtoInventory(this);
		}
	}
}


