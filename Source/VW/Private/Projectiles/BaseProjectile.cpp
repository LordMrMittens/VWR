 // Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/BaseProjectile.h"
#include "Characters/Interfaces/CharacterInterface.h"
#include "Components/AudioPlayerComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/StaticMeshcomponent.h"


ABaseProjectile::ABaseProjectile()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	SetRootComponent(Mesh);

}

void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ABaseProjectile::OnProjectileOverlaps);
}

void ABaseProjectile::SetupProjectile(float StartingRotation, float StartingAltitude, float HorzDirection, float VertDirection)
{
	Rotation = StartingRotation;
	Altitude = StartingAltitude;
	HorizontalDirection = HorzDirection;
	VerticalDirection = VertDirection;
}

void ABaseProjectile::OnProjectileOverlaps(AActor* OverlappedActor, AActor* OtherActor)
{


	if (!IsValid(OtherActor)) return;
	AudioPlayerComponent->PlaySoundOnce(FName("Hit"));
	if(ICharacterInterface* HitActor = Cast<ICharacterInterface>(OtherActor))
	{
		ProjectileData.Location = GetActorLocation();
		HitActor->GetHit(ProjectileData);
	}
	//Spawn VFX SFX
	UNiagaraComponent* MuzzleFlash = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitSystem, GetActorLocation());
	Destroy();
}


void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(HorizontalDirection, VerticalDirection, DeltaTime);
}
