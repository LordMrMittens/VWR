// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "EnemySpawner.generated.h"

class ABaseEnemy;
/**
 * 
 */
USTRUCT()
struct FWaveSpawnParams
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere)
    TArray<TSubclassOf<ABaseEnemy>> EnemyClassesToSpawn; // can be made a TPair to allocate exact enemies to spawn by class
    UPROPERTY(EditAnywhere)
    int32 NumberToSpawn{ 50 }; //will disappear When TPair logic created
    UPROPERTY(EditAnywhere)
    float MaxTimeBetweenSpawns{ 5.0f };
    UPROPERTY(EditAnywhere)
    float MinTimeBetweenSpawns{ 0.5f };

};

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
