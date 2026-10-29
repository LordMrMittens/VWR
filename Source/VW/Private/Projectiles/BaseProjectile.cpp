// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/BaseProjectile.h"
#include "Components/StaticMeshcomponent.h"


ABaseProjectile::ABaseProjectile()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	SetRootComponent(Mesh);

}

void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(0, MoveDirectionAndSpeed, DeltaTime);
}
