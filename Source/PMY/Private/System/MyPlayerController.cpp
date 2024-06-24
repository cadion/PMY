// Fill out your copyright notice in the Description page of Project Settings.


#include "System/MyPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "System/MyGameInstance.h"
#include "System/MySingleton.h"
#include "UI/DynamicActionGroup/DynamicActionGroupWidget.h"

AMyPlayerController::AMyPlayerController()
{
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	
	
	if(MyGameInstance->GetMySingleton())
	{
		if(IsLocalPlayerController())
		{
			DynamicActionGroup = CreateWidget<UDynamicActionGroupWidget>(this, MyGameInstance->GetMySingleton()->DynamicActionGroupClass);
			DynamicActionGroup->AddToViewport();	
		}
		
	}
	
}
