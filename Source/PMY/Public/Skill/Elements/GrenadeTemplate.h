// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillTemplate.h"
#include "GrenadeTemplate.generated.h"

/**
 * 
 */
UCLASS()
class PMY_API AGrenadeTemplate : public ASkillTemplate
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

#pragma region Common Properties
public:
	ESkillType SkillType = ESkillType::WeaponEquipped;
#pragma endregion Common Properties
};
