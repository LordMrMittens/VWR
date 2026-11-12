// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GunComponent.h"
#include "Projectiles/BaseProjectile.h"

// Sets default values for this component's properties
UGunComponent::UGunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGunComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UGunComponent::Shoot(float Rotation, float Altitude, FIntPoint Offset)
{
	Shoot(Rotation, Altitude, GetComponentLocation(), Offset);
}

void UGunComponent::Shoot(float Rotation, float Altitude, FVector SpawnPoint, FIntPoint Offset)
{
	LastProjectile = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, SpawnPoint, GetComponentRotation());
	if (!LastProjectile.IsValid()) return;
	LastProjectile->SetupProjectile(Rotation + Offset.X, Altitude + Offset.Y, HorizontalDirection, VerticalDirection);
}


// Called every frame
void UGunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

