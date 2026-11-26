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

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	FWaveSpawnParams InitialWave;

	UPROPERTY(VisibleAnywhere, Category = "Spawning")
	TObjectPtr<UEnemySpawner>EnemySpawner;
};
