// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Guns/GunWeaponActor.h"


void AGunWeaponActor::EndSwithcing()
{
	Super::EndSwithcing();

	switch (ActionState)
	{
		case EGunActionState::Loading:
			Load();
			break;

		case EGunActionState::Reloading:
			Reload();
			break;
		
		default:
			break;
	}
}


void AGunWeaponActor::UnEquipped()
{
	switch (ActionState)
	{
		case EGunActionState::OnFiring:
			//TODO : Stop Firing ( Anim )
			true? ActionState = EGunActionState::Idle : ActionState = EGunActionState::Reloading; // TODO : 남은 탄약이 없으면 Reloading으로 전환
			break;

		case EGunActionState::Charging:
			ActionState = EGunActionState::Idle;
			break;

		case EGunActionState::Loading:
			//TODO : Stop Loading ( Anim )
			break;

		case EGunActionState::Reloading:
			//TODO : Stop Reloading ( Anim ), 단발식 충전이면 추가 처리
			break;

		default:
			break;
	}
	ToHipFire();
	Super::UnEquipped();
}

void AGunWeaponActor::TryTriggerAction()
{
	Super::TryTriggerAction();
}

void AGunWeaponActor::TriggerAction()
{
}

void AGunWeaponActor::Charge()
{
}

void AGunWeaponActor::Fire()
{
}

void AGunWeaponActor::Load()
{
}

void AGunWeaponActor::Reload()
{
}

void AGunWeaponActor::ToHipFire()
{
	AimingState = EGunAimingState::HipFire;
	//TODO : Camera Property 변경
	//TODO : Character에 SetCameraProperty( CharacterCameraPorperty, WeaponCameraProperty ) 넣어서 호출하도록 할거임. 각 변수는 클래스에서 가지고
}

void AGunWeaponActor::ToAiming()
{
	AimingState = EGunAimingState::AimedFire;
	//TODO : Camera Property 변경
}

void AGunWeaponActor::ToAimDownSight()
{
	//TODO : Camera Change 후 State 변환
	AimingState = EGunAimingState::AimDownSight;
}
