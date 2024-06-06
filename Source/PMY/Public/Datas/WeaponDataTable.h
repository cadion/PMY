// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WeaponDataTable.generated.h"


class UWeaponComponent;

USTRUCT()
struct FWeaponData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UWeaponComponent> WeaponClass;
	UPROPERTY(EditDefaultsOnly)
	FString WeaponName;
	//TODO : CrossHair Widget Class
};

/**
 * 
 */
UCLASS()
class PMY_API UWeaponDataTable : public UDataTable
{
	GENERATED_BODY()
	
};
