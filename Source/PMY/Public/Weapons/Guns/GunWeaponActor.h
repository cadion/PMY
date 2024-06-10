// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/WeaponActor.h"
#include "GunWeaponActor.generated.h"

UENUM(BlueprintType)
enum class EGunActionState : uint8
{
	Idle = 0,
	Charging,
	OnFiring,
	Loading,
	Reloading,
};

UENUM(BlueprintType)
enum class EGunAimingState : uint8
{
	HipFire = 0,
	AimedFire,
	AimDownSight,
};

UENUM(BlueprintType)
enum class EFireMode : uint8
{
	FullAuto = 0,
	SemiAuto,
	Burst,
	Manual,
	MovableCharge,
	UnMovableCharge,
};

/**
 * 
 */
UCLASS()
class PMY_API AGunWeaponActor : public AWeaponActor
{
	GENERATED_BODY()

public:


#pragma region Action
public:
	virtual void EndSwithcing() override;
	virtual void UnEquipped() override;
	virtual void TryTriggerAction() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void TriggerAction();
	UFUNCTION(BlueprintCallable)
	virtual void Charge();
	UFUNCTION(BlueprintCallable)
	virtual void Fire();
	UFUNCTION(BlueprintCallable)
	virtual void Load();
	UFUNCTION(BlueprintCallable)
	virtual void Reload();

	UFUNCTION(BlueprintCallable)
	void ToHipFire();
	UFUNCTION(BlueprintCallable)
	void ToAiming();
	UFUNCTION(BlueprintCallable)
	void ToAimDownSight();
	
#pragma endregion Action
	
#pragma region Property
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EFireMode FireMode = EFireMode::FullAuto;
#pragma endregion Property

#pragma region State
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EGunActionState ActionState = EGunActionState::Idle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EGunAimingState AimingState = EGunAimingState::HipFire;
#pragma endregion State
	
};
