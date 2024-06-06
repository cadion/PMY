// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/MyCharacter.h"
#include "Logging/LogMacros.h"
#include "PlayerCharacter.generated.h"

class UMySingleton;
class UMyGameInstance;
class UWeaponInputMap;
class UWeaponComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UENUM(BlueprintType)
enum class EWeaponActionState : uint8
{
	DoNothing = 0 UMETA(DisplayName = "Do Nothing"),
	Loading UMETA(DisplayName = "Loading"),
	Reloading UMETA(DisplayName = "Reloading"),
	Switching UMETA(DisplayName = "Switching"),
	OnAttack UMETA(DisplayName = "On Attack"),
	OnAttackCancellable UMETA(DisplayName = "On Attack Cancellable"),
};

UENUM(BlueprintType)
enum class ECrowdControlState : uint8
{
	Normal = 0 UMETA(DisplayName = "Normal"),
	Stunned UMETA(DisplayName = "Stunned"),
	KnockedBack UMETA(DisplayName = "Knocked Back"),
	KnockedDown UMETA(DisplayName = "Knocked Down"),
	
};

UCLASS(config=Game)
class APlayerCharacter : public AMyCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
#pragma region Components
public:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** FPS Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FPSCamera;

	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UWeaponComponent* WeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivate))
	TObjectPtr<UWeaponInputMap> WeaponInputMap;

	//TODO : Asset Table 참조로 변경 예정
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UWeaponComponent> WeaponComponentClass;
	

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** Returns FPSCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFPSCamera() const { return FPSCamera; }

#pragma endregion Components
#pragma region ExternalReferences
public:
	UPROPERTY()
	TObjectPtr<UMyGameInstance> MyGameInstance;
	UPROPERTY()
	TObjectPtr<UMySingleton> MySingleton;
#pragma endregion ExternalReferences
#pragma region Inputs
public:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
#pragma endregion Inputs
#pragma region Weapon Inputs
	UFUNCTION()
	void TryContinuousPrimaryFire(const FInputActionValue& Value);
	UFUNCTION()
	void TryContinuousSecondaryFire(const FInputActionValue& Value);
	UFUNCTION()
	void TrySinglePrimaryFire(const FInputActionValue& Value);
	UFUNCTION()
	void TrySingleSecondaryFire(const FInputActionValue& Value);
#pragma endregion Weapon Inputs

#pragma region Character Properties

public:
	UFUNCTION(BlueprintCallable)
	FVector GetAimStartWorldLocation() const;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FVector AimStartOffset;
	
	
#pragma endregion Character Properties
#pragma region Tick Events variables
public:
	UPROPERTY(BlueprintReadWrite)
	bool bCheckAimOnTick = true;

	UPROPERTY(BlueprintReadOnly)
	FHitResult HitUnderAimOnTick;

	UPROPERTY(BlueprintReadOnly)
	bool bHitUnderAimOnTick = false;

#pragma endregion  Tick Events variables
#pragma region Action
protected:
	UFUNCTION(BlueprintCallable)
	void ChangeWeapon(int32 WeaponIndex);

	UFUNCTION(BlueprintCallable)
	void StartAiming();
	UFUNCTION(BlueprintCallable)
	void EndAiming();
	
#pragma endregion Action
#pragma region states

public:
	bool TryChangeAimingState(bool bNewAiming);
	bool TryChangeWeaponActionState(EWeaponActionState NewState);
	bool TryChangeCrowdControlState(ECrowdControlState NewState);
	FORCEINLINE bool GetAiming() const { return bIsAiming; }
	FORCEINLINE EWeaponActionState GetWeaponActionState() const { return WeaponActionState; }
	FORCEINLINE ECrowdControlState GetCrowdControlState() const { return CrowdControlState; }
	
private:
	bool bIsAiming = false;
	EWeaponActionState WeaponActionState = EWeaponActionState::DoNothing;
	ECrowdControlState CrowdControlState = ECrowdControlState::Normal;

#pragma endregion states
};

