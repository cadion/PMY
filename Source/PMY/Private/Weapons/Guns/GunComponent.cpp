// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Guns/GunComponent.h"

#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Characters/PlayerCharacters/PlayerCharacter.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

class APlayerCharacter;

void UGunComponent::BeginPlay()
{
	Super::BeginPlay();
	if (Owner)
	{
		USpringArmComponent* CameraBoom = Owner->GetCameraBoom();
		UCameraComponent* FollowCamera = Owner->GetFollowCamera();
		if (CameraBoom && FollowCamera)
		{
			CameraBoom->TargetArmLength = CameraSet.CameraDistance;
			FollowCamera->FieldOfView = CameraSet.FOV;
			FollowCamera->SetRelativeLocation(CameraSet.CameraOffset);
			CameraBoom->SocketOffset = CameraSet.CameraLookAtOffset;
		}
	}

	SurplusAmmo = MaxSurplusAmmo;
	CurrentMagazine = MagazineCapacity;
}



void UGunComponent::TryContinuousPrimaryFire(const FInputActionValue& Value)
{
	Super::TryContinuousPrimaryFire(Value);
	if(CheckCanPrimaryFire())
	{
		DoWeaponPrimaryFire();
	}
}

void UGunComponent::TrySinglePrimaryFire(const FInputActionValue& Value)
{
	Super::TrySinglePrimaryFire(Value);
	if(CheckCanPrimaryFire())
	{
		DoWeaponPrimaryFire();
	}
	
}

bool UGunComponent::CheckCanPrimaryFire()
{
	if(Owner)
	{
		if(Owner->GetWeaponActionState() == EWeaponActionState::DoNothing &&
		Owner->GetCrowdControlState() == ECrowdControlState::Normal)
		{
			if (GetWorld()->TimeSeconds > (LastFireTime + (1 / FireRate)) or LastFireTime == 0.0f)
			{
				return true;	
			}
			
		}	
	}	
	return false;
}

void UGunComponent::DoWeaponPrimaryFire()
{
	FVector MuzzlePosition = this->GetSocketLocation("Muzzle");
	//발사 효과
	//DrawDebugLine(GetWorld(), HandBonePosition, Owner->HitUnderAimOnTick.ImpactPoint, FColor::Red, false, -1.0f, 0, 1.0f);
	if(MuzzleFlash)
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFlash, this, "Muzzle", MuzzlePosition, FRotator::ZeroRotator, EAttachLocation::KeepWorldPosition, true);
	}
	switch(ProjectileType)
	{
		case EProjectileType::Hitscan:
			// Spawn Niagara System At Location
			break;
		case EProjectileType::Projectile:
			//Projectile
			break;
	}
	LastFireTime = GetWorld()->TimeSeconds;

	//피격 효과
	if(Owner->bHitUnderAimOnTick)
	{
		AActor* Target = Owner->HitUnderAimOnTick.GetActor();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hit Actor : %s"), *Target->GetName()));
		if(Target)
		{
			//I want Apply damage to "Target"
			UGameplayStatics::ApplyDamage(Target, GetWeaponATK(), Owner->GetController(), Owner, UDamageType::StaticClass());
			UPrimitiveComponent* PrimitiveRoot = Cast<UPrimitiveComponent>(Target->GetRootComponent());
			if(PrimitiveRoot && PrimitiveRoot->IsSimulatingPhysics())
			{
				FVector HitDirection = Owner->HitUnderAimOnTick.ImpactPoint - MuzzlePosition;
				PrimitiveRoot->AddImpulseAtLocation(HitDirection * Momentum, Owner->HitUnderAimOnTick.ImpactPoint);
			}
		}
	}
	DoWeaponPrimaryFireBP();
}

void UGunComponent::TryReload()
{
	bool bCanReload = true; //TODO : 리로드 가능조건 체크. 잔탄, 액션

	CurrentMagazine >= MagazineCapacity? bCanReload = false : bCanReload = true;
	SurplusAmmo <= 0? bCanReload = false : bCanReload = true;
	
	if(bCanReload)
	{
		DoReload();
	}
}

void UGunComponent::DoReload()
{
	//TODO : 애니메이션 재생 및 Notify 대기
	AdjustReloadAmmo();
}

void UGunComponent::AdjustReloadAmmo()
{
	int32 NeedAmmo = MagazineCapacity - CurrentMagazine;
	if(SurplusAmmo >= NeedAmmo)
	{
		SurplusAmmo -= NeedAmmo;
		CurrentMagazine = MagazineCapacity;
	}
	else
	{
		CurrentMagazine += SurplusAmmo;
		SurplusAmmo = 0;
	}
}
