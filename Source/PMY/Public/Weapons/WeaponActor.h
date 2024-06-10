// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"


class APlayerCharacter;

UCLASS()
class PMY_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region ExternalRef

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	APlayerCharacter* OwnerPlayerCharacter;

#pragma endregion ExternalRef
	
#pragma region Component
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	class USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	class USkeletalMeshComponent* WeaponMesh;
#pragma endregion Component
	
#pragma region Action
	UFUNCTION(BlueprintCallable)
	virtual void Owned(APlayerCharacter* NewOwnerPlayerCharacter);
	UFUNCTION(BlueprintCallable)
	virtual void Equipped();
	UFUNCTION()
	virtual void EndSwithcing();
	UFUNCTION(BlueprintCallable)
	virtual void UnEquipped();

	UFUNCTION(BlueprintCallable)
	virtual void TryTriggerAction();
	
#pragma endregion Action
	
#pragma region Property
#pragma endregion Property
	
#pragma region State
#pragma endregion State
};
