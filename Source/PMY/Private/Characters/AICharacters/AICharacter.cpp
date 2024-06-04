// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AICharacters/AICharacter.h"

AAICharacter::AAICharacter()
{
	TeamNumber = 2;
}

void AAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

float AAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	//TODO : 체력 감소 조건 및 액션이벤트, 감쇄효과 등 추가
	Health -= DamageAmount;
	if(Health <= 0)
	{
		TryDeath(2.f);
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}
