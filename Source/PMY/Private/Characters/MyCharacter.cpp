// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MyCharacter.h"

#include "Characters/PlayerCharacters/StateManagerComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StateManagerComponent = CreateDefaultSubobject<UStateManagerComponent>(TEXT("StateManagerComponent"));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::TryDeath(float TimeToDeath)
{
	//TODO: 죽지 않을 조건 추가
	bool bCanDie = true;
	if(bCanDie && DeathTimerHandle.IsValid() == false)
	{
		//TODO: 죽기 전 애니메이션 등 액션 추가
		GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AMyCharacter::Death, TimeToDeath, false);	
	}
}

void AMyCharacter::Death()
{
	//TODO: 죽기 직전 폭발 등 효과 추가
	Destroy();
}

