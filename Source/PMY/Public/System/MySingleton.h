// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MySingleton.generated.h"

class UWeaponInputMap;
class UDynamicActionGroupWidget;
/**
 * 
 */
UCLASS(Blueprintable)
class PMY_API UMySingleton : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> DynamicActionGroupClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UWeaponInputMap> WeaponInputMapData;
};
