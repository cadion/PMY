// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/WeaponComponent.h"
#include "MeleeComponent.generated.h"

/**
 * 
 */
UCLASS()
class PMY_API UMeleeComponent : public UWeaponComponent
{
	GENERATED_BODY()

public:
	UMeleeComponent();


#pragma region Action
public:
	virtual void TrySinglePrimaryFire(const FInputActionValue& Value) override;
	UFUNCTION()
	void DoSinglePrimaryFire();
	UFUNCTION(BlueprintNativeEvent)
	void DoSinglePrimaryFireBP();

#pragma endregion Action
};
