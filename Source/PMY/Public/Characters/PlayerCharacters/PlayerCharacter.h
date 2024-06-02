// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/MyCharacter.h"
#include "Logging/LogMacros.h"
#include "PlayerCharacter.generated.h"

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

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** FPS Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FPSCamera;
	
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

public:
	APlayerCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;

#pragma region Tick Events variables
public:
	UPROPERTY(BlueprintReadWrite)
	bool bCheckAimOnTick = true;

	UPROPERTY(BlueprintReadOnly)
	FHitResult HitUnderAimOnTick;

	UPROPERTY(BlueprintReadOnly)
	bool bHitUnderAimOnTick = false;

#pragma endregion  Tick Events variables
	
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** Returns FPSCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFPSCamera() const { return FPSCamera; }

public:
	bool TryChangeWeaponActionState(EWeaponActionState NewState);
	bool TryChangeCrowdControlState(ECrowdControlState NewState);
	FORCEINLINE EWeaponActionState GetWeaponActionState() const { return WeaponActionState; }
	FORCEINLINE ECrowdControlState GetCrowdControlState() const { return CrowdControlState; }
private:
	EWeaponActionState WeaponActionState = EWeaponActionState::DoNothing;
	ECrowdControlState CrowdControlState = ECrowdControlState::Normal;
};

