// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/VoidWingGameMode.h"
#include "Gameplay/EnemySpawner.h"

void AVoidWingGameMode::OnPlayerDeath(float LastRotation, float LastAltitude)
{
}

void AVoidWingGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (UWorld* World = GetWorld())
	{
		EnemySpawner = World->GetSubsystem<UEnemySpawner>();
		if (EnemySpawner)
		{
			EnemySpawner->SetDefaultVariables(FVector::ZeroVector, 2000.f, 2500.f);
			EnemySpawner->UpdateWaveSpawningParams(InitialWave);
		}
	}
}
