// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ZombieController.h"

#include "Characters/AICharacters/MyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Touch.h"
#include "Perception/AISense_Touch.h"

AZombieController::AZombieController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));
	TouchConfig = CreateDefaultSubobject<UAISenseConfig_Touch>(TEXT("TouchConfig"));

	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->ConfigureSense(*HearingConfig);
	AIPerceptionComponent->ConfigureSense(*DamageConfig);
	AIPerceptionComponent->ConfigureSense(*TouchConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AZombieController::OnPerceptionUpdated);
}

void AZombieController::BeginPlay()
{
	Super::BeginPlay();
}

void AZombieController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Sight stimulus detected from: %s"), *Actor->GetName());
	}
	else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hearing stimulus detected from: %s"), *Actor->GetName());
	}
	else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Damage>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Damage stimulus detected from: %s"), *Actor->GetName());
	}
	else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Touch>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Touch stimulus detected from: %s"), *Actor->GetName());
	}
}
