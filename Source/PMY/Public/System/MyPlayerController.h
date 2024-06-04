// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UMyGameInstance;
class UDynamicActionGroupWidget;
/**
 * 
 */
UCLASS()
class PMY_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerController();
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	UDynamicActionGroupWidget* GetDynamicActionGroup() const { return DynamicActionGroup; }
protected:
	UPROPERTY()
	TObjectPtr<UMyGameInstance> MyGameInstance;
	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
	UDynamicActionGroupWidget* DynamicActionGroup;
	
};
