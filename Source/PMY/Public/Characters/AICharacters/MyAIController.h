// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class PMY_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
	//AMyAIController();

	//virtual void BeginPlay() override;
	//virtual void OnPossess(APawn* InPawn) override;
	//virtual void OnUnPossess() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UBehaviorTree* BehaviorTree;
};
