// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/WeaponComponent.h"
#include "GunComponent.generated.h"

/**
 * Weapon중 Gun 전용 항목
 */
USTRUCT(BlueprintType)
struct FGunCameraSet
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	float FPSCameraFOV = 90.0f;
	
};

UENUM(BlueprintType)
enum class ELoadType : uint8
{
	FullyAutomatic = 0	UMETA(DisplayName = "Fully Automatic"),
	SemiAutomatic = 1 	UMETA(DisplayName = "Semi Automatic"),
	BoltAction = 2 		UMETA(DisplayName = "Bolt Action"),
};

UCLASS()
class PMY_API UGunComponent : public UWeaponComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	bool TryWeaponPrimaryFire();

	UFUNCTION(BlueprintCallable)
	void DoWeaponPrimaryFire();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun", meta = (AllowPrivate))
	FGunCameraSet GunCameraSet;

	

private:
	
};
