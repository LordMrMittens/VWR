 // Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/BaseProjectile.h"
#include "Components/StaticMeshcomponent.h"


ABaseProjectile::ABaseProjectile()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	SetRootComponent(Mesh);

}

void ABaseProjectile::SetupProjectile(float StartingRotation, float StartingAltitude, float HorzDirection, float VertDirection)
{
	Rotation = StartingRotation;
	Altitude = StartingAltitude;
	HorizontalDirection = HorzDirection;
	VerticalDirection = VertDirection;
}

void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(HorizontalDirection, VerticalDirection, DeltaTime);
}
