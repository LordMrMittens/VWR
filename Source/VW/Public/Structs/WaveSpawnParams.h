#pragma once

#include "CoreMinimal.h"
#include "WaveSpawnParams.generated.h"

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