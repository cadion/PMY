// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Guns/GunComponent.h"

#include "Camera/CameraComponent.h"
#include "Characters/PlayerCharacters/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"

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
}

bool UGunComponent::TryWeaponPrimaryFire()
{
	if(Owner->GetWeaponActionState() == EWeaponActionState::DoNothing &&
		Owner->GetCrowdControlState() == ECrowdControlState::Normal)
	{
		DoWeaponPrimaryFire();
		return true;
	}
	
	return false;
}

void UGunComponent::DoWeaponPrimaryFire()
{
	DrawDebugLine(GetWorld(), Owner->GetActorLocation(), Owner->HitUnderAimOnTick.ImpactPoint, FColor::Red, false, 1.0f, 0, 1.0f);
}


