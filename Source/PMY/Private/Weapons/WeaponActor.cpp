// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponActor.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(Root);
	
}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponActor::Owned(UWeaponManagerComponent* NewWeaponManagerComponent)
{
	WeaponManagerComponent = NewWeaponManagerComponent;
}

void AWeaponActor::Equipped()
{
	EndSwithcing(); //TODO Switching Anim Play, Anim Notify에서 EndSwitching 호출
}

void AWeaponActor::EndSwithcing()
{
}

void AWeaponActor::UnEquipped()
{
}

void AWeaponActor::TryTriggerAction()
{
}

