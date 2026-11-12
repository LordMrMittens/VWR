// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/InstancedMasterEnemySquad.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/GunComponent.h"
#include "Structs/ProjectileCollision.h"
#include "Structs/InstanceStats.h"
#include "Utils/MovementUtils.h"
#include "DrawDebugHelpers.h" 

AInstancedMasterEnemySquad::AInstancedMasterEnemySquad()
{
	EnemyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(EnemyRoot);
	ISMAlienMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ISM"));
	ISMAlienMesh->SetupAttachment(EnemyRoot);
	GunComponent = CreateDefaultSubobject<UGunComponent>(TEXT("Gun"));
	GunComponent->SetupAttachment(EnemyRoot);
}

void AInstancedMasterEnemySquad::BeginPlay()
{
	Super::BeginPlay();
	checkf(IsValid(ISMAlienMesh), TEXT("Enemy Squad has no valid ISM Component"));

	float SpawnRotation = bDebugSpawn ? DebugSpawnRotation : FMath::RandRange(0.0f, 360.0f);
	SetInitialPosition(SpawnRotation, StartingHeight);

	for (int32 r = 0; r < NumberOfRows; r++)
	{
		for (int32 c = 0; c < NumberOfColumns; c++) 
		{
			SpawnInvaderISM(r, c);
		}
	}

	CurrentHorzDirection = FMath::RandBool() ? 1 : -1;
	HorizontalSpeed = CurrentHorzDirection + DefaultHorizontalSpeed;
	float TimeToShoot = FMath::RandRange(MinTimeBetweenShots, MaxTimeBetweenShots);
	GetWorldTimerManager().SetTimer(ShootingTimerHandle, this, &AInstancedMasterEnemySquad::Shoot, TimeToShoot);
	StopAndMoveHorizontally();
}
void AInstancedMasterEnemySquad::GetHit(FProjectileCollision CollisionData)
{
	TArray<int32> HitInvadersIndexes = ISMAlienMesh->GetInstancesOverlappingSphere(CollisionData.Location, CollisionData.DamageRadius, true);
	for (int32 Index : HitInvadersIndexes)
	{
		PerInstanceStats[Index].bIsDead = (PerInstanceStats[Index].Health += CollisionData.Damage) <= 0;
		if (PerInstanceStats[Index].bIsDead)
		{
			//SFX and VFX, Score, Items Spawned etc
			ISMAlienMesh->UpdateInstanceTransform(Index, FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector::ZeroVector), false, true, true);
			if (--AliveEnemiesInSquad <= 0) 
			{
				//other squad full wipe logic
				GetWorldTimerManager().ClearTimer(MovementTimerHandle);
				GetWorldTimerManager().ClearTimer(ShootingTimerHandle);
				Destroy();
			}
		}
	}
}


void AInstancedMasterEnemySquad::SpawnInvaderISM(int32 Row, int32 Column)
{
	FSpawnOffsetParams Params;
	CalculateInstanceOffset(Row, Column, Params);
	
	FVector SpawnLocation = MovementUtils::CalculateUpdatedPosition(Params.SpawnRotation, Params.SpawnAltitude, DistanceFromCenter, CenterPoint);
	FRotator SpawnLookAt = GetActorRotation() + RotationalOffset; // Can edit Mesh so this is unnecesary
	FTransform SpawnTransform (SpawnLookAt, SpawnLocation, FVector{ 1.0f });
	int32 InstanceIndex = ISMAlienMesh->AddInstance(SpawnTransform, true);
	PerInstanceStats.Emplace( FInstanceStats{ InstanceIndex,AlienHealth, false, FVector2D(Params.RotationOffset, Params.AltitudeOffset) });
	AliveEnemiesInSquad++;
}

void AInstancedMasterEnemySquad::CalculateInstanceOffset(int32 RowIndex, int32 ColumnIndex, FSpawnOffsetParams& OutSpawnParams)
{
	OutSpawnParams.RotationOffset = HorizontalSpacing * ColumnIndex;
	OutSpawnParams.AltitudeOffset = VerticalSpacing * RowIndex;
	OutSpawnParams.SpawnRotation = MovementUtils::GetNormalisedRotation(Rotation + OutSpawnParams.RotationOffset);
	OutSpawnParams.SpawnAltitude = Altitude + OutSpawnParams.AltitudeOffset;
}

void AInstancedMasterEnemySquad::StopAndMoveVertically()
{
	HorizontalSpeed = 0;
	CurrentVertDirection = -1;
	VerticalSpeed = DefaultVerticalSpeed;
	GetWorldTimerManager().ClearTimer(MovementTimerHandle);
	GetWorldTimerManager().SetTimer(MovementTimerHandle,this,&AInstancedMasterEnemySquad::StopAndMoveHorizontally, VerticalMovementDuration, false);
}

void AInstancedMasterEnemySquad::StopAndMoveHorizontally()
{
	VerticalSpeed = 0;
	CurrentHorzDirection *= -1;
	HorizontalSpeed = DefaultHorizontalSpeed;
	GetWorldTimerManager().ClearTimer(MovementTimerHandle);
	GetWorldTimerManager().SetTimer(MovementTimerHandle, this, &AInstancedMasterEnemySquad::StopAndMoveVertically, HorizontalMovementDuration, false);
}
void AInstancedMasterEnemySquad::Shoot()
{
	int32 RandomIndex = FMath::RandRange(0, PerInstanceStats.Num()-1);
	if (PerInstanceStats.IsValidIndex(RandomIndex) && !PerInstanceStats[RandomIndex].bIsDead) {
		float ShootRotation = Rotation + PerInstanceStats[RandomIndex].Offset.X;
		float ShootAltitude = Altitude + PerInstanceStats[RandomIndex].Offset.Y;
		FTransform InstanceTransform;
		ISMAlienMesh->GetInstanceTransform(RandomIndex, InstanceTransform, true);
	GunComponent->Shoot(ShootRotation, ShootAltitude, InstanceTransform.GetLocation(), ShootingOffset);
	}
	float TimeToShoot = FMath::RandRange(MinTimeBetweenShots, MaxTimeBetweenShots);
	GetWorldTimerManager().SetTimer(ShootingTimerHandle, this, &AInstancedMasterEnemySquad::Shoot, TimeToShoot);
}
