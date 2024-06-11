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
	UFUNCTION(BlueprintCallable)
	void TrySpawnWeapon(TSubclassOf<AWeaponActor> NewWeaponClass, bool bEquipWhenSpawned = true);
	UFUNCTION(Server, Reliable)
	void TrySpawnWeapon_Server(TSubclassOf<AWeaponActor> NewWeaponClass, uint8 TargetSlot, bool bEquipWhenSpawned);
	UFUNCTION(Client, Reliable)
	void TrySpawnWeapon_Client(AWeaponActor* NewWeapon, uint8 TargetSlot, bool bEquipWhenSpawned);
	
	
	
public:
	UFUNCTION(BlueprintCallable)
	void SwitchWeapon();
	UFUNCTION()
	void CallChangeWeapon(uint8 TargetSlot);
	UFUNCTION(Server, Reliable)
	void ChangeWeapon_Server(uint8 TargetSlot);
	UFUNCTION(Client, Reliable)
	void ChangeWeapon_Client(uint8 TargetSlot);
	UFUNCTION()
	void ChangeWeapon(uint8 TargetSlot);
	UFUNCTION(BlueprintCallable)
	void DropWeapon(uint8 TargetSlot);
	UFUNCTION(Server, Reliable)
	void DropWeapon_Server(uint8 TargetSlot);
	UFUNCTION(Client, Reliable)
	void DropWeapon_Client(uint8 TargetSlot);
	
#pragma endregion Action

#pragma region State
	UPROPERTY(BlueprintReadWrite)
	uint8 CurrentWeaponSlot = 0;
#pragma endregion State
};
