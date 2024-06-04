// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class PMY_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCharacter")
	int TeamNumber = 0; // 0 is neutral, 1 is player, 2 is enemy

#pragma region Common Properties
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCharacter")
	float MaxHealth = 100.0f;
	UPROPERTY(BlueprintReadWrite, Category = "MyCharacter")
	float Health = MaxHealth;

#pragma endregion Common Properties

#pragma region Common Action

public:
	UFUNCTION(BlueprintCallable)
	virtual void TryDeath(float TimeToDeath = 1.0f);
	UFUNCTION(BlueprintCallable)
	void Death();

#pragma endregion Common Action
};
