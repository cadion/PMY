// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponComponent.generated.h"

struct FEnhancedInputActionEventBinding;
class APlayerCharacter;
class UInputMappingContext;
/**
 * 모든 무기의 기본 클래스
 * 무기의 타입과 관계없이 항상 정의되어야 하는 항목들
 */
USTRUCT(BlueprintType)
struct FWeaponCameraSet
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	float FOV = 90.0f;
	UPROPERTY(EditAnywhere)
	float CameraDistance = 400.0f;
	UPROPERTY(EditAnywhere)
	FVector CameraOffset = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere)
	FVector CameraLookAtOffset = FVector(0.0f, 0.0f, 0.0f);
};

USTRUCT(BlueprintType)
struct FMovementSetting
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	bool bOrientationTowardMovement = false;
	UPROPERTY(EditAnywhere)
	float SpeedMagnitude = 1.0f;
	
};

UCLASS()
class PMY_API UWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	FWeaponCameraSet GetCameraSet() const { return CameraSet; }
	FMovementSetting GetMovementSetting() const { return MovementSetting; }

	UFUNCTION(BlueprintCallable)
	bool EquipWeapon();
	UFUNCTION(BlueprintCallable)
	bool UnEquipWeapon();

#pragma region InitialSetting
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerCharacter> Owner;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivate))
	FWeaponCameraSet CameraSet;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivate))
	FMovementSetting MovementSetting;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivate))
	TSubclassOf<UAnimInstance> WeaponAnimInstance;
	
#pragma endregion InitialSetting
#pragma region WeaponParameters
public:
	UFUNCTION(BlueprintCallable)
	float GetWeaponATK() const { return WeaponATK; }
	UFUNCTION(BlueprintCallable)
	void SetWeaponATK(float NewWeaponATK) { WeaponATK = NewWeaponATK; }
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivate))
	float WeaponATK = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivate))
	float FireRate = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivate))
	float Momentum = 0.3f * 330.0f; // kg * cm / s
	

#pragma endregion WeaponParameters
#pragma region WeaponState
	UPROPERTY(BlueprintReadWrite)
	float LastFireTime = 0.0f;
#pragma endregion WeaponState
#pragma region Inputs
public:
	UFUNCTION()
	virtual void SetPlayerInputComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponInput", meta = (AllowPrivate))
	UInputMappingContext* WeaponMappingContext;

#pragma endregion Inputs
#pragma region Actions
	UFUNCTION(BlueprintCallable)
	virtual void TryContinuousPrimaryFire(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	virtual void TrySinglePrimaryFire(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	virtual void TryContinuousSecondaryFire(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	virtual void TrySingleSecondaryFire(const FInputActionValue& Value);
#pragma endregion Actions
};
