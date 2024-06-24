// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieController.generated.h"

class UAISenseConfig_Damage;
class UAISenseConfig_Hearing;
class UAISenseConfig_Sight;
class UAISenseConfig_Touch;
struct FAIStimulus;
/**
 * 
 */
UCLASS()
class PMY_API AZombieController : public AAIController
{
	GENERATED_BODY()

public:
	AZombieController();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY()
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY()
	UAISenseConfig_Hearing* HearingConfig;

	UPROPERTY()
	UAISenseConfig_Damage* DamageConfig;

	// Contact with the AI Perception Component
	UPROPERTY()
	UAISenseConfig_Touch* TouchConfig;

	

	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
};
