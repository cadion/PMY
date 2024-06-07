// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponComponent.h"

#include "DelayAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/PlayerCharacters/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Datas/WeaponInputMap.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//Set Owners Camera Setting
	 Owner = Cast<APlayerCharacter>(GetOwner());
	 
	LastFireTime = 0.f;
}

bool UWeaponComponent::EquipWeapon()
{
	if(Owner)
	{
		if(WeaponAnimInstance)
    	{
    		Owner->GetMesh()->SetAnimInstanceClass(WeaponAnimInstance);
    	}
	}
	if (Owner) // Camera Setting
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
	if (Owner) // Movement Setting
	{
		if(MovementSetting.bOrientationTowardMovement == true)
		{
			Owner->bUseControllerRotationYaw = false;
			Cast<UCharacterMovementComponent>(Owner->GetMovementComponent())->bOrientRotationToMovement = true;
		}
		else if(MovementSetting.bOrientationTowardMovement == false)
		{
			Owner->bUseControllerRotationYaw = true;
			Cast<UCharacterMovementComponent>(Owner->GetMovementComponent())->bOrientRotationToMovement = false;
		}
	}
	
	
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
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetWorld()->GetFirstLocalPlayerFromController()))
	{
		Subsystem->RemoveMappingContext(WeaponMappingContext);
	}
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

void UWeaponComponent::TrySinglePrimaryFire(const FInputActionValue& Value)
{
}

void UWeaponComponent::TryContinuousSecondaryFire(const FInputActionValue& Value)
{
}

void UWeaponComponent::TrySingleSecondaryFire(const FInputActionValue& Value)
{
}


