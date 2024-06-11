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

void UWeaponManagerComponent::TrySpawnWeapon(TSubclassOf<AWeaponActor> NewWeaponClass, bool bEquipWhenSpawned)
{
	for (int i = 0; i < WeaponSlot.Num(); i++)
	{
		if(WeaponSlot[i] == nullptr)
		{
			TrySpawnWeapon_Server(NewWeaponClass, i, bEquipWhenSpawned);
			return;
		}
	}
	
	{
		DropWeapon(CurrentWeaponSlot);
		TrySpawnWeapon_Server(NewWeaponClass, CurrentWeaponSlot, bEquipWhenSpawned);
		return;
	}
	
}

void UWeaponManagerComponent::TrySpawnWeapon_Server_Implementation(TSubclassOf<AWeaponActor> NewWeaponClass, uint8 TargetSlot, bool bEquipWhenSpawned = true)
{
	AWeaponActor* NewWeapon = GetWorld()->SpawnActor<AWeaponActor>(NewWeaponClass);
	
	if(bEquipWhenSpawned)
	{
		ChangeWeapon(TargetSlot);
		WeaponSlot[CurrentWeaponSlot] = NewWeapon;
	}
		
	//TODO : SlotCheck
	// Weapon에 manager, owner 할당해주고 Weapon 내 Owned, Equipped 처리
}

void UWeaponManagerComponent::TrySpawnWeapon_Client_Implementation(AWeaponActor* NewWeapon, uint8 TargetSlot,
	bool bEquipWhenSpawned)
{
	ChangeWeapon(TargetSlot);
	WeaponSlot[CurrentWeaponSlot] = NewWeapon;
}

void UWeaponManagerComponent::SwitchWeapon()
{
	if(CurrentWeaponSlot == 0)
	{
		ChangeWeapon(1);
	}
	else
	{
		ChangeWeapon(0);
	}
}



void UWeaponManagerComponent::CallChangeWeapon(uint8 TargetSlot)
{
	ChangeWeapon(TargetSlot);
	ChangeWeapon_Server(TargetSlot);
}

void UWeaponManagerComponent::ChangeWeapon_Server_Implementation(uint8 TargetSlot)
{
	ChangeWeapon(TargetSlot);
	ChangeWeapon_Client(TargetSlot);
}

void UWeaponManagerComponent::ChangeWeapon_Client_Implementation(uint8 TargetSlot)
{
	if (!OwnerPlayerCharacter->IsLocallyControlled())
	{
		ChangeWeapon(TargetSlot);
	}
}

void UWeaponManagerComponent::ChangeWeapon(uint8 TargetSlot)
{
	if ( CurrentWeaponSlot == TargetSlot )
	{
		return;
	}
	WeaponSlot[CurrentWeaponSlot]->UnEquipped();
	WeaponSlot[TargetSlot]->Equipped();
}

void UWeaponManagerComponent::DropWeapon(uint8 TargetSlot)
{
	DropWeapon_Server(TargetSlot);
}

void UWeaponManagerComponent::DropWeapon_Server_Implementation(uint8 TargetSlot)
{
	
	// Weapon Slot 비우고
	// Weapon Destroy 및 메모리할당 해제하고
	// Client 에선 전처리하고
	// Server 에선 Broadcast 하고
}

void UWeaponManagerComponent::DropWeapon_Client_Implementation(uint8 TargetSlot)
{
}


