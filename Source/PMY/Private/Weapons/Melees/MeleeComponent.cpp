// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Melees/MeleeComponent.h"

UMeleeComponent::UMeleeComponent()
{
	MovementSetting.bOrientationTowardMovement = true;
}

void UMeleeComponent::TrySinglePrimaryFire(const FInputActionValue& Value)
{
	Super::TrySinglePrimaryFire(Value);
	//CoordAction이나 Condition 추가해야 함
	DoSinglePrimaryFire();
}

void UMeleeComponent::DoSinglePrimaryFire()
{
	DoSinglePrimaryFireBP();
}

void UMeleeComponent::DoSinglePrimaryFireBP_Implementation()
{
}
