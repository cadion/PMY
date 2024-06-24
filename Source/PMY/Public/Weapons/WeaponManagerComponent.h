// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponManagerComponent.generated.h"


class AWeaponActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PMY_API UWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponManagerComponent();
	virtual void InitializeComponent() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region ExternalRef
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	class APlayerCharacter* OwnerPlayerCharacter = nullptr;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Weapon")
	TArray<AWeaponActor*> WeaponSlot;
#pragma  endregion ExternalRef
	
#pragma region Action

public:

	
	
#pragma endregion Action

#pragma region State
	UPROPERTY(BlueprintReadWrite)
	uint8 CurrentWeaponSlot = 0;
#pragma endregion State

#pragma region Property
	UPROPERTY()
	FName EquippedSocketName = FName("hand_r");
	UPROPERTY()
	FName UnEquippedSocketName = FName("spine_02");
#pragma endregion Property
};
