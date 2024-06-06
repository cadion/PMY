// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacters/PlayerCharacterAnimInstance.h"

#include "Characters/PlayerCharacters/PlayerCharacter.h"

UPlayerCharacterAnimInstance::UPlayerCharacterAnimInstance()
{
}

void UPlayerCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	// PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	StartAimDelegate.BindUObject(this, &UPlayerCharacterAnimInstance::StartAim);
	EndAimDelegate.BindUObject(this, &UPlayerCharacterAnimInstance::EndAim);
}

void UPlayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(PlayerCharacter)
	{
		bIsAiming = PlayerCharacter->GetAiming();
	}
}


