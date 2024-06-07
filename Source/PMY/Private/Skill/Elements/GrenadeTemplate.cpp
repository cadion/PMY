// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Elements/GrenadeTemplate.h"

#include "Characters/MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Skill/SkillManagerComponent.h"

void AGrenadeTemplate::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AMyCharacter* MyCharacter = SkillManager->MyCharacter;
	if(MyCharacter)
	{
		//draw ballistic trajectory debug line start from hand_r socket to camera forward direction with gravity parameter on every tick
		FPredictProjectilePathParams PredictParams(0.f, MyCharacter->GetMesh()->GetSocketLocation("hand_r"), MyCharacter->GetMesh()->GetSocketRotation("hand_r").Vector() * 1000.f, 10.f, UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
		PredictParams.StartLocation = MyCharacter->GetMesh()->GetSocketLocation("hand_r");
		PredictParams.LaunchVelocity = MyCharacter->GetController()->GetControlRotation().Vector() * 1500.f;
		PredictParams.MaxSimTime = 1.f;
		PredictParams.bTraceWithCollision = false;
		PredictParams.SimFrequency = 20.f;
		PredictParams.OverrideGravityZ = 0.f;
		PredictParams.DrawDebugType = EDrawDebugTrace::None;
		FPredictProjectilePathResult PredictResult;
		bool bHit = UGameplayStatics::PredictProjectilePath(this, PredictParams, PredictResult);
		for (int i = 0; i+1 < PredictResult.PathData.Num(); i++)
		{
			DrawDebugLine(GetWorld(), PredictResult.PathData[i].Location, PredictResult.PathData[i+1].Location, FColor::Red, false, -1.f, 0, 1.f);
		}
		
		
		
		
		
	}
}
