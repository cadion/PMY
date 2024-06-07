// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillManagerComponent.h"

#include "Characters/MyCharacter.h"
#include "Skill/SkillTemplate.h"

// Sets default values for this component's properties
USkillManagerComponent::USkillManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USkillManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	MyCharacter = Cast<AMyCharacter>(GetOwner());
	
}


// Called every frame
void USkillManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USkillManagerComponent::TryUseSkill()
{
	bool bCanUseSkill = true; //TODO : 스킬 사용 가능 여부 판단
	if(bCanUseSkill)
	{
		UseSkill();
	}
}

void USkillManagerComponent::UseSkill()
{
	const TObjectPtr<ASkillTemplate> UsedSkill = GetWorld()->SpawnActor<ASkillTemplate>(TestSkill);
	UsedSkill->SkillManager = this;
	UsedSkill->InitializeSkill();
}

