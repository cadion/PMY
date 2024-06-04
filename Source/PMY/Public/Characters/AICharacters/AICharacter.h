// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/MyCharacter.h"
#include "AICharacter.generated.h"

/**
 * 
 */
UCLASS()
class PMY_API AAICharacter : public AMyCharacter
{
	GENERATED_BODY()

public:
	AAICharacter();

	virtual void Tick(float DeltaSeconds) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
};
