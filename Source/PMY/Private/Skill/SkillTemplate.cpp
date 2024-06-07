// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillTemplate.h"

#include "Skill/SkillManagerComponent.h"

// Sets default values
ASkillTemplate::ASkillTemplate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkillTemplate::InitializeSkill()
{
	if(SkillManager != nullptr)
	{
		SetOwner(SkillManager->GetOwner());	
	}
	
}

// Called when the game starts or when spawned
void ASkillTemplate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkillTemplate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

