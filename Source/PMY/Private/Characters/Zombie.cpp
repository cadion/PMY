// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Zombie.h"

#include "AbilitySystemComponent.h"

// Sets default values
AZombie::AZombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	

}

// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();
	ASC->InitAbilityActorInfo(this, this);
	int32 InputId = 0;
	for (auto Ability : Abilities)
	{
		FGameplayAbilitySpecHandle Handle = ASC->GiveAbility(FGameplayAbilitySpec(Ability, 1, InputId++));
	}
}

// Called every frame
void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AZombie::GetAbilitySystemComponent() const
{
	return ASC;
}

void AZombie::ActivateAbility(int32 Index)
{
	ASC->TryActivateAbility(ASC->FindAbilitySpecFromInputID(Index)->Handle);
	
}

