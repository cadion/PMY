// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponInputMap.generated.h"

class UInputAction;
/**
 * 
 */
UCLASS()
class PMY_API UWeaponInputMap : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UInputAction* PrimaryContinuousFire;
	UPROPERTY(EditAnywhere)
	UInputAction* PrimarySingleFire;
	UPROPERTY(EditAnywhere)
	UInputAction* SecondaryContinuousFire;
	UPROPERTY(EditAnywhere)
	UInputAction* SecondarySingleFire;
	UPROPERTY(EditAnywhere)
	UInputAction* ReCharge;
	UPROPERTY(EditAnywhere)
	UInputAction* TogglePrimaryCharge;
	UPROPERTY(EditAnywhere)
	UInputAction* ToggleSecondaryCharge;
};
