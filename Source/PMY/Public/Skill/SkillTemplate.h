// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillTemplate.generated.h"

class USkillManagerComponent;

UENUM()
enum class ESkillType : uint8
{
	Immediate,
	WeaponEquipped,
	
};

UCLASS()
class PMY_API ASkillTemplate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillTemplate();
	void InitializeSkill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
#pragma region External Reference
	USkillManagerComponent* SkillManager;
#pragma endregion External Reference
	
	
#pragma region Common Properties
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill")
	ESkillType SkillType = ESkillType::Immediate;
#pragma endregion Common Properties

};
