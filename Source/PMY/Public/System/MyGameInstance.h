// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

class UDynamicActionGroupWidget;
class UMySingleton;
/**
 * 
 */
UCLASS()
class PMY_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();
	virtual void Init() override;

	FORCEINLINE TObjectPtr<UMySingleton> GetMySingleton() { return MySingleton; }

private:
	TObjectPtr<UMySingleton> MySingleton;
	TObjectPtr<UDynamicActionGroupWidget> DynamicActionGroup;
};
