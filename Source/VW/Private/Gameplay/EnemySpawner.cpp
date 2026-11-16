// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EnemySpawner.h"
#include "Characters/Enemies/BaseEnemy.h"
#include "Utils/MovementUtils.h"

UEnemySpawner::UEnemySpawner()
{
}

void UEnemySpawner::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UEnemySpawner::Deinitialize()
{
	Super::Deinitialize();
}

void UEnemySpawner::SetDefaultVariables(const FVector InCenterPoint, float InDistanceFromCenter, float InSpawnAltitude)
{
	CenterPoint = InCenterPoint;
	DistanceFromCenter = InDistanceFromCenter;
	SpawnAltitude = InSpawnAltitude;
}

void UEnemySpawner::UpdateWaveSpawningParams(const FWaveSpawnParams& SpawningParameters)
{
	WaveSpawningParameters = SpawningParameters;
	EnemiesInWave = WaveSpawningParameters.NumberToSpawn;
	float TimeForNextSpawn = FMath::RandRange(WaveSpawningParameters.MinTimeBetweenSpawns, WaveSpawningParameters.MaxTimeBetweenSpawns);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &UEnemySpawner::SpawnEnemyAtRandomRotation, TimeForNextSpawn, false);
}

void UEnemySpawner::SpawnEnemyAtRandomRotation()
{
	if (WaveSpawningParameters.NumberToSpawn-- > 0)
	{
		int32 ClassToSpawn = FMath::RandRange(0, WaveSpawningParameters.EnemyClassesToSpawn.Num() - 1);
		float SpawnRotation = FMath::RandRange(0.0f, 360.0f);
		FTransform SpawnTransform = MovementUtils::CalculateInitialTransform(SpawnRotation, SpawnAltitude, DistanceFromCenter, CenterPoint);
		ABaseEnemy* SpawnedEnemy = GetWorld()->SpawnActorDeferred<ABaseEnemy>(WaveSpawningParameters.EnemyClassesToSpawn[ClassToSpawn], SpawnTransform);
		
		if (!IsValid(SpawnedEnemy)) return;

		SpawnedEnemy->UpdateInitialPositionVariable(SpawnRotation, SpawnAltitude);
		//SpawnedEnemy->SetInitialPosition(SpawnRotation, SpawnAltitude); probably not needed in the enemy class anymore
		SpawnedEnemy->FinishSpawning(SpawnTransform);

		float TimeForNextSpawn = FMath::RandRange(WaveSpawningParameters.MinTimeBetweenSpawns, WaveSpawningParameters.MaxTimeBetweenSpawns);
		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &UEnemySpawner::SpawnEnemyAtRandomRotation, TimeForNextSpawn, false);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		OnWaveEnds.Broadcast();
	}
}

void UEnemySpawner::OnEnemyDied()
{
	if (--EnemiesInWave <= 0) OnWaveEnds.Broadcast();
}
