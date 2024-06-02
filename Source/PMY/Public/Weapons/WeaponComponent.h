// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PlayerCharacters/PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponComponent.generated.h"

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
	float CameraDistance = 100.0f;
	UPROPERTY(EditAnywhere)
	FVector CameraOffset = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere)
	FVector CameraLookAtOffset = FVector(0.0f, 0.0f, 0.0f);
};

UCLASS()
class PMY_API UWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();
	virtual void BeginPlay() override;

	FWeaponCameraSet GetCameraSet() const { return CameraSet; }

protected:
	APlayerCharacter* Owner;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivate))
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivate))
	FWeaponCameraSet CameraSet;
	
};