// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Structs/WaveSpawnParams.h"
#include "Gameplay/Interfaces/GameModeInterface.h"
#include "VoidWingGameMode.generated.h"

class UEnemySpawner;
struct FWaveSpawnParams;

/**
 * 
 */

UCLASS()
class VW_API AVoidWingGameMode : public AGameModeBase, public IGameModeInterface
{
	GENERATED_BODY()
public:

	UFUNCTION()
	virtual void OnPlayerDeath(float LastRotation, float LastAltitude) override;
	UFUNCTION()
	void RespawnPlayer(float LastRotation, float LastAltitude);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Enemy Spawning")
	FWaveSpawnParams InitialWave;
	UPROPERTY(EditAnywhere, Category = "Enemy Spawning")
	float DefaultAltitude{ 2500.0f };

	UPROPERTY(VisibleAnywhere, Category = "Enemy Spawning")
	TObjectPtr<UEnemySpawner>EnemySpawner;

	FTimerHandle PlayerRespawnTimerHandle;

private:
	UPROPERTY(EditAnywhere, Category = "Player Spawning")
	float RespawnDelay{ 3.0f };
	UPROPERTY(EditAnywhere, Category = "Player Spawning")
	float DistanceToCenter{ 2000.0f };
	UPROPERTY(EditAnywhere, Category = "Player Spawning")
	FVector CenterPoint{ 0.0f };
};
