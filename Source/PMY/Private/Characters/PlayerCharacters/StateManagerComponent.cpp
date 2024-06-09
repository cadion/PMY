// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacters/StateManagerComponent.h"

// Sets default values for this component's properties
UStateManagerComponent::UStateManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStateManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStateManagerComponent::SetCurrentActionProperty(FActionProperty& NewActionProperty)
{
	CurrentActionProperty = NewActionProperty;
}

bool UStateManagerComponent::CheckCanAction(FActionProperty& ActionProperty)
{
	if(ActionProperty.bCanMove && CurrentActionProperty.bCanMove)
	{
		return true;
	}
	
	return true;
}

bool UStateManagerComponent::TrySlow(float Ratio, float Time)
{
	return false;
}

bool UStateManagerComponent::TryBurn(float Damage, float Time)
{
	return false;
}

bool UStateManagerComponent::TryPoison(float Damage, float Time)
{
	return false;
}

bool UStateManagerComponent::TryStun(float Time)
{
	return false;
}

bool UStateManagerComponent::TryKnockdown(float Time)
{
	return false;
}

bool UStateManagerComponent::TryKnockback(FVector Direction, float Distance, float Time)
{
	return false;
}

