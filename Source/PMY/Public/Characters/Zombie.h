// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Zombie.generated.h"

class UGameplayAbility;

UCLASS()
class PMY_API AZombie : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void ActivateAbility(int32 Index);
	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> ASC;
	
};
