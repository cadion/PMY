// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponManagerComponent.h"

#include "Characters/PlayerCharacters/PlayerCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Weapons/WeaponActor.h"

// Sets default values for this component's properties
UWeaponManagerComponent::UWeaponManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	WeaponSlot.Init(nullptr, 2);
}

void UWeaponManagerComponent::InitializeComponent()
{
	Super::InitializeComponent();
	OwnerPlayerCharacter = Cast<APlayerCharacter>(GetOwner());
}

void UWeaponManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWeaponManagerComponent, WeaponSlot);
}


// Called when the game starts
void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

