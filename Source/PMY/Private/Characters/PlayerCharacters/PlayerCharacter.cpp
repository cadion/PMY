// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/PlayerCharacters/PlayerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Characters/PlayerCharacters/PlayerCharacterAnimInstance.h"
#include "Characters/PlayerCharacters/StateManagerComponent.h"
#include "Datas/WeaponDataTable.h"
#include "Datas/WeaponInputMap.h"
#include "Kismet/GameplayStatics.h"
#include "Skill/SkillManagerComponent.h"
#include "System/MyGameInstance.h"
#include "System/MySingleton.h"
#include "Weapons/WeaponComponent.h"

struct FWeaponData;
DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATP_ThirdPersonCharacter
APlayerCharacter::APlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	FPSCamera->SetupAttachment(RootComponent);
	FPSCamera->bUsePawnControlRotation = true;

	SkillManagerComponent = CreateDefaultSubobject<USkillManagerComponent>(TEXT("SkillManagerComponent"));

	

	TeamNumber = 1;

	

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void APlayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	MySingleton = Cast<UMySingleton>(GEngine->GameSingleton);

	if(WeaponComponentClass)
	{
		ChangeWeapon(1);
	}
	
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bCheckAimOnTick)
	{
		FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam;
		Params.AddIgnoredActor(this);
		
		APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		FVector StartPoint = CameraManager->GetCameraLocation();
		FVector EndPoint = CameraManager->GetCameraLocation() + (CameraManager->GetActorForwardVector() * 10000);
		bHitUnderAimOnTick = GetWorld()->LineTraceSingleByChannel(HitUnderAimOnTick, StartPoint, EndPoint, ECollisionChannel::ECC_Visibility, Params);
		if(!bHitUnderAimOnTick)
		{
			FHitResult HitResultWhenNoHit = FHitResult();
			HitResultWhenNoHit.Location = EndPoint;
			HitResultWhenNoHit.ImpactPoint = EndPoint;
			HitResultWhenNoHit.ImpactNormal = GetActorForwardVector();
			HitResultWhenNoHit.Normal = GetActorForwardVector();
			HitUnderAimOnTick = HitResultWhenNoHit;
		}
	}

	if(bCameraTransitioning)
	{
		UpdateCamera(DeltaSeconds);
	}
	
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	//TODO : 체력 감소 조건 및 액션이벤트, 감쇄효과 등 추가
	Health -= DamageAmount;
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void APlayerCharacter::ChangeWeapon(int32 WeaponIndex)
{
	UDataTable* WeaponDataTable = MySingleton->WeaponDataTable;
	if(WeaponDataTable)
	{
		FWeaponData* WeaponData = WeaponDataTable->FindRow<FWeaponData>(FName(*FString::FromInt(WeaponIndex)), TEXT("WeaponIndex"));
		if(WeaponData)
		{
			if(WeaponComponent!=nullptr)
			{
				WeaponComponent->UnEquipWeapon();
				WeaponComponent->DestroyComponent();	
			}
			
			WeaponComponent = NewObject<UWeaponComponent>(this, WeaponData->WeaponClass);
			WeaponComponent->RegisterComponent();
			//WeaponComponent->SetupAttachment(GetMesh(), TEXT("hand_r"));
			WeaponComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("hand_r"));
			WeaponComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
			WeaponComponent->EquipWeapon();
		}
	}
}

void APlayerCharacter::StartAiming()
{
	if(UPlayerCharacterAnimInstance* PCAnimInstance = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		PCAnimInstance->StartAimDelegate.ExecuteIfBound();
	}
}

void APlayerCharacter::EndAiming()
{
	if(UPlayerCharacterAnimInstance* PCAnimInstance = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		PCAnimInstance->EndAimDelegate.ExecuteIfBound();
	}
}

bool APlayerCharacter::TryChangeAimingState(bool bNewAiming)
{
	return true;
}

bool APlayerCharacter::TryChangeWeaponActionState(EWeaponActionState NewState)
{
	if(true) //TODO : Add condition
	{
		WeaponActionState = NewState;
		return true;
	}
	return false;
}

bool APlayerCharacter::TryChangeCrowdControlState(ECrowdControlState NewState)
{
	if(true) //TODO : Add condition
	{
		CrowdControlState = NewState;
		return true;
	}
	return false;
}

void APlayerCharacter::SetDesireCameraSet(const FWeaponCameraSet& NewCameraSet, float TransitionSpeed)
{
	DesireCameraSet = NewCameraSet;
	CameraTransitionSpeed = TransitionSpeed;
	if (IsEqualCameraSet(CurrentCameraSet, DesireCameraSet))
	{
		bCameraTransitioning = false;
	}
	else
	{
		if(CameraTransitionSpeed <= 0.f)
		{
			SetCamera(DesireCameraSet);
		}
		bCameraTransitioning = true;
	}
}

bool APlayerCharacter::IsEqualCameraSet(const FWeaponCameraSet& CameraSet1, const FWeaponCameraSet& CameraSet2)
{
	if (CameraSet1.FOV == CameraSet2.FOV &&
		CameraSet1.CameraDistance == CameraSet2.CameraDistance &&
		CameraSet1.CameraOffset == CameraSet2.CameraOffset &&
		CameraSet1.CameraLookAtOffset == CameraSet2.CameraLookAtOffset)
	{
		return true;
	}
	return false;
}

void APlayerCharacter::UpdateCamera(float DeltaSeconds)
{
	float CurrentCameraDistance = abs(CurrentCameraSet.CameraDistance - DesireCameraSet.CameraDistance); 
	if(CurrentCameraDistance < DeltaSeconds * CameraTransitionSpeed)
	{
		SetCamera(DesireCameraSet);
		bCameraTransitioning = false;
	}
	else
	{
		FVector NewCameraOffset = FMath::VInterpTo(CurrentCameraSet.CameraOffset, DesireCameraSet.CameraOffset, DeltaSeconds, CameraTransitionSpeed);
		float NewCameraDistance = FMath::FInterpTo(CurrentCameraSet.CameraDistance, DesireCameraSet.CameraDistance, DeltaSeconds, CameraTransitionSpeed);
		FVector NewCameraLookAtOffset = FMath::VInterpTo(CurrentCameraSet.CameraLookAtOffset, DesireCameraSet.CameraLookAtOffset, DeltaSeconds, CameraTransitionSpeed);
		SetCamera(FWeaponCameraSet{DesireCameraSet.FOV, NewCameraDistance, NewCameraOffset, NewCameraLookAtOffset});
	}
}

void APlayerCharacter::SetCamera(FWeaponCameraSet NewCameraSet)
{
	CurrentCameraSet = NewCameraSet;
	FollowCamera->FieldOfView = NewCameraSet.FOV;
	CameraBoom->TargetArmLength = NewCameraSet.CameraDistance;
	FollowCamera->SetRelativeLocation(NewCameraSet.CameraOffset);
	CameraBoom->SocketOffset = NewCameraSet.CameraLookAtOffset;
}

//////////////////////////////////////////////////////////////////////////
// Input

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	InputComponent = PlayerInputComponent;
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		// Weapon Input Map
		//TObjectPtr<UWeaponInputMap> WeaponInputMap = Cast<UMySingleton>(GEngine->GameSingleton)->WeaponInputMapData;
		if (WeaponInputMap)
		{
			EnhancedInputComponent->BindAction(WeaponInputMap->PrimaryContinuousFire, ETriggerEvent::Triggered, this, &APlayerCharacter::TryContinuousPrimaryFire);
			EnhancedInputComponent->BindAction(WeaponInputMap->SecondaryContinuousFire, ETriggerEvent::Triggered, this, &APlayerCharacter::TryContinuousSecondaryFire);
			EnhancedInputComponent->BindAction(WeaponInputMap->PrimarySingleFire, ETriggerEvent::Triggered, this, &APlayerCharacter::TrySinglePrimaryFire);
			EnhancedInputComponent->BindAction(WeaponInputMap->SecondarySingleFire, ETriggerEvent::Triggered, this, &APlayerCharacter::TrySingleSecondaryFire);
		}
		
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
	
}

void APlayerCharacter::TryContinuousPrimaryFire(const FInputActionValue& Value)
{
	if(WeaponComponent)
	{
		WeaponComponent->TryContinuousPrimaryFire(Value);
	}
}

void APlayerCharacter::TryContinuousSecondaryFire(const FInputActionValue& Value)
{
	if(WeaponComponent)
	{
		WeaponComponent->TryContinuousSecondaryFire(Value);
	}
}

void APlayerCharacter::TrySinglePrimaryFire(const FInputActionValue& Value)
{
	if (WeaponComponent)
	{
		WeaponComponent->TrySinglePrimaryFire(Value);
	}
}

void APlayerCharacter::TrySingleSecondaryFire(const FInputActionValue& Value)
{
	if(WeaponComponent)
	{
		WeaponComponent->TrySingleSecondaryFire(Value);
	}
}

FVector APlayerCharacter::GetAimStartWorldLocation() const
{
	return GetActorTransform().TransformPosition(AimStartOffset);
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}