// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Guns/GunComponent.h"

#include "EnhancedInputComponent.h"
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
}



void UGunComponent::TryContinuousPrimaryFire(const FInputActionValue& Value)
{
	Super::TryContinuousPrimaryFire(Value);
	if(Owner->GetWeaponActionState() == EWeaponActionState::DoNothing &&
		Owner->GetCrowdControlState() == ECrowdControlState::Normal)
	{
		DoWeaponPrimaryFire();
	}
	
}

void UGunComponent::DoWeaponPrimaryFire()
{
	FVector HandBonePosition = Owner->GetMesh()->GetSocketLocation("hand_r");
	//Owner->GetAimStartWorldLocation()
	DrawDebugLine(GetWorld(), HandBonePosition, Owner->HitUnderAimOnTick.ImpactPoint, FColor::Red, false, -1.0f, 0, 1.0f);
	if(Owner->bHitUnderAimOnTick)
	{
		AActor* Target = Owner->HitUnderAimOnTick.GetActor();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hit Actor : %s"), *Target->GetName()));
		if(Target)
		{
			//I want Apply damage to "Target"
			UGameplayStatics::ApplyDamage(Target, GetWeaponATK(), Owner->GetController(), Owner, UDamageType::StaticClass());
			UPrimitiveComponent* PrimitiveRoot = Cast<UPrimitiveComponent>(Target->GetRootComponent());
			if(PrimitiveRoot)
			{
				FVector HitDirection = Owner->HitUnderAimOnTick.ImpactPoint - HandBonePosition;
				PrimitiveRoot->AddImpulseAtLocation(HitDirection * Momentum, Owner->HitUnderAimOnTick.ImpactPoint);
			}
		}
	}
}
