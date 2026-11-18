// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GunComponent.h"
#include "NiagaraSystem.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"
#include "Utils/MovementUtils.h"
#include "Projectiles/BaseProjectile.h"

// Sets default values for this component's properties
UGunComponent::UGunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UGunComponent::Shoot(float Rotation, float Altitude, FVector2D Offset)
{
	if (!IsValid(ProjectileClass) || !MuzzleFlashSystem) return;
	FTransform SpawnTransform = MovementUtils::CalculateInitialTransform(Rotation + Offset.X, Altitude + Offset.Y, 2000, FVector::ZeroVector);
	if (ABaseProjectile* LastProjectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(ProjectileClass, SpawnTransform))
	{
		LastProjectile->SetupProjectile(Rotation + Offset.X, Altitude + Offset.Y, HorizontalDirection, VerticalDirection);
		LastProjectile->FinishSpawning(SpawnTransform);
		UNiagaraComponent* MuzzleFlash = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MuzzleFlashSystem, SpawnTransform.GetLocation(), SpawnTransform.Rotator());
	}
}



