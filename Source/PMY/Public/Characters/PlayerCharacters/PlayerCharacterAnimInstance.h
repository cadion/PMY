// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerCharacterAnimInstance.generated.h"

class APlayerCharacter;

DECLARE_DELEGATE(StartAimDelegate)
DECLARE_DELEGATE(EndAimDelegate)
/**
 * 
 */
UCLASS()
class PMY_API UPlayerCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerCharacterAnimInstance();
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

#pragma region Delegates
public:
	StartAimDelegate StartAimDelegate;
	EndAimDelegate EndAimDelegate;

protected:
	UFUNCTION()
	void StartAim() {bIsAiming = true;}
	UFUNCTION()
	void EndAim() {bIsAiming = false;}
#pragma endregion Delegates
	
	

#pragma region Properties
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Owner")
	TObjectPtr<APlayerCharacter> PlayerCharacter;
	
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float MovementSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	bool bIsAiming;

#pragma endregion Properties
};