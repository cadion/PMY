// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UENUM(BlueprintType)
enum EGunActionState : uint8
{
	Idle = 0,
	OnFiring,
	NeedLoad,
	Reloading,
	NeedReload,
	MovableCharging,
	UnMovableCharging,
};

UENUM(BlueprintType)
enum EGunAimingState
{
	HipFire = 0,
	AimedFire,
	AimDownSight,
};

UENUM()
enum EFireMode
{
	FullAuto = 0,
	SemiAuto,
	Burst,
	Manual,	
};

UCLASS()
class PMY_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
