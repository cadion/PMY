// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponComponent.h"

#include "DelayAction.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/PlayerCharacters/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//Set Owners Camera Setting
	Owner = Cast<APlayerCharacter>(GetOwner());
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
		
	EquipWeapon();
}

bool UWeaponComponent::EquipWeapon()
{
	bool bCanEquipWeapon = true; //TODO : Check if can equip weapon
	if(bCanEquipWeapon)
	{
		SetPlayerInputComponent();
		return true;
	}
	
	return false;
}

bool UWeaponComponent::UnEquipWeapon()
{
	
	return true;
}

void UWeaponComponent::SetPlayerInputComponent()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetWorld()->GetFirstLocalPlayerFromController()))
	{
		Subsystem->AddMappingContext(WeaponMappingContext, 1);
	}
}

void UWeaponComponent::TryContinuousPrimaryFire(const FInputActionValue& Value)
{
}

void UWeaponComponent::TryContinuousSecondaryFire(const FInputActionValue& Value)
{
}
