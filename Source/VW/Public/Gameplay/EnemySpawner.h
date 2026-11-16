// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Structs/WaveSpawnParams.h"
#include "EnemySpawner.generated.h"

class ABaseEnemy;
/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnWaveEnds);

UCLASS()
class VW_API UEnemySpawner : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	UEnemySpawner();

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    
    void SetDefaultVariables(const FVector InCenterPoint,float InDistanceFromCenter, float InSpawnAltitude);
    void UpdateWaveSpawningParams(const FWaveSpawnParams& SpawningParameters);
    void SpawnEnemyAtRandomRotation();

    FOnWaveEnds OnWaveEnds;
private:
    UFUNCTION()
    void OnEnemyDied();

    FWaveSpawnParams WaveSpawningParameters;

    FVector CenterPoint{ 0.0f };
    float DistanceFromCenter{ 2000.0f };
    float SpawnAltitude{ 2500.0f };
    int32 EnemiesInWave{ 0 };

    FTimerHandle SpawnTimerHandle;
	
};
