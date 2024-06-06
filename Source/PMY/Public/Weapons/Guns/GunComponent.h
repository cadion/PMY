// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/WeaponComponent.h"
#include "GunComponent.generated.h"

class UCurveVector;
class UNiagaraSystem;
struct FInputActionValue;
class UInputAction;
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
	ManulLoading = 2 		UMETA(DisplayName = "Bolt Action"),
};

UENUM(BlueprintType)
enum class EProjectileType : uint8
{
	Hitscan = 0	UMETA(DisplayName = "Hitscan"),
	Projectile = 1 	UMETA(DisplayName = "Projectile"),
};

UCLASS()
class PMY_API UGunComponent : public UWeaponComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;



protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun", meta = (AllowPrivate))
	FGunCameraSet GunCameraSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun", meta = (AllowPrivate))
	ELoadType LoadType = ELoadType::FullyAutomatic;

#pragma region Inputs
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponInput", meta = (AllowPrivate))
	UInputAction* PrimaryFire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponInput", meta = (AllowPrivate))
	UInputAction* SecondaryFire;

#pragma endregion Inputs

#pragma region Actions

public:
	virtual void TryContinuousPrimaryFire(const FInputActionValue& Value) override;
	virtual void TrySinglePrimaryFire(const FInputActionValue& Value) override;

	UFUNCTION()
	bool CheckCanPrimaryFire();

	UFUNCTION(BlueprintCallable)
	void DoWeaponPrimaryFire();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DoWeaponPrimaryFireBP();
	UFUNCTION(BlueprintCallable)
	void TryReload();
	UFUNCTION(BlueprintCallable)
	void DoReload();
	UFUNCTION(BlueprintCallable)
	void AdjustReloadAmmo();
	

	

#pragma endregion Actions

#pragma region State
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun", meta = (AllowPrivate))
	int32 CurrentMagazine = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun", meta = (AllowPrivate))
	int32 SurplusAmmo = 0;
#pragma endregion State
	
#pragma region Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivate))
	EProjectileType ProjectileType = EProjectileType::Hitscan;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivate))
	int32 MagazineCapacity = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivate))
	bool bInfiniteAmmo = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivate))
	int32 MaxSurplusAmmo = 90;
	
	//Make Variable for FVector Curve Graph for recoil
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunRecoil", meta = (AllowPrivate))
	UCurveVector* GunRecoilCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunRecoil", meta = (AllowPrivate))
	float VerticalRecoilMin = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunRecoil", meta = (AllowPrivate))
	float VerticalRecoilMax = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunRecoil", meta = (AllowPrivate))
	float HorizontalRecoilMin = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunRecoil", meta = (AllowPrivate))
	float HorizontalRecoilMax = 0.0f;

#pragma endregion Property

#pragma region ReferenceResrouces
protected:
	UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = "Gun")
	UNiagaraSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = "Gun", meta = (EditCondition="ProjectileType == EProjectileType::Hitscan"))
	UNiagaraSystem* HitScanProjectile;
	UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = "Gun", meta = (EditCondition="ProjectileType == EProjectileType::Projectile"))
	TSubclassOf<AActor> ProjectileClass;
	
#pragma endregion ReferenceResrouces
	
};
