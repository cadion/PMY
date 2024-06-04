// Fill out your copyright notice in the Description page of Project Settings.


#include "System/MyGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "System/MySingleton.h"
#include "UI/DynamicActionGroup/DynamicActionGroupWidget.h"

UMyGameInstance::UMyGameInstance()
{
	
}

void UMyGameInstance::Init()
{
	Super::Init();
	MySingleton = Cast<UMySingleton>(GEngine->GameSingleton);
}
