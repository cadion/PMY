// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateManagerComponent.generated.h"


USTRUCT(BlueprintType)
struct FActionProperty
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	bool bCanMove = true;
	UPROPERTY(EditAnywhere)
	bool bCanJump = true;
	UPROPERTY(EditAnywhere)
	bool bCanCancel = true;
	UPROPERTY(EditAnywhere)
	bool bCanOverrideCancelNoti = false;

	FActionProperty()
	{
		bCanMove = true;
		bCanJump = true;
		bCanCancel = true;
		bCanOverrideCancelNoti = false;
	}
	FActionProperty(bool CanMove, bool CanJump, bool CanCancel, bool CanOverrideCancelNoti)
	{
		bCanMove = CanMove;
		bCanJump = CanJump;
		bCanCancel = CanCancel;
		bCanOverrideCancelNoti = CanOverrideCancelNoti;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PMY_API UStateManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStateManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region State
public:
	UFUNCTION(BlueprintCallable)
	void SetCurrentActionProperty(FActionProperty& NewActionProperty);
	UFUNCTION(BlueprintCallable)
	bool CheckCanAction(FActionProperty& ActionProperty);
	
	// Notifier들 활성 영역
	UPROPERTY(BlueprintReadWrite)
	bool bInHitSection = false;
	UPROPERTY(BlueprintReadWrite)
	bool bInGuardSection = false;
	UPROPERTY(BlueprintReadWrite)
	bool bInDodgeSection = false;
	UPROPERTY(BlueprintReadWrite)
	bool bInCanCancelSection = false;

protected:
	UPROPERTY()
	FActionProperty DefaultIdle = FActionProperty(false, false, false, true);
	UPROPERTY()
	FActionProperty CurrentActionProperty = DefaultIdle;

public:
	UFUNCTION(BlueprintCallable)
	bool TrySlow(float Ratio, float Time);
	UFUNCTION(BlueprintCallable)
	bool TryBurn(float Damage, float Time);
	UFUNCTION(BlueprintCallable)
	bool TryPoison(float Damage, float Time);
	UFUNCTION(BlueprintCallable)
	bool TryStun(float Time);
	UFUNCTION(BlueprintCallable)
	bool TryKnockdown(float Time);
	UFUNCTION(BlueprintCallable)
	bool TryKnockback(FVector Direction, float Distance, float Time);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	float SlowRatio = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	float SlowLeftTime = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	float BurnDamage = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	float BurnLeftTime = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	float PoisonDamage = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	float PoisonLeftTime = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	float StunLeftTime = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	float KnockdownLeftTime = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	bool bKnockback = false;

#pragma endregion State
};
