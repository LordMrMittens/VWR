// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/VoidWingGameMode.h"
#include "Gameplay/EnemySpawner.h"

void AVoidWingGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("GameModeActive"));
	if (UWorld* World = GetWorld())
	{
		UE_LOG(LogTemp, Display, TEXT("Got world"));
		EnemySpawner = World->GetSubsystem<UEnemySpawner>();
		if (EnemySpawner)
		{
			UE_LOG(LogTemp, Display, TEXT("Got Enemy Spawner"));
			EnemySpawner->SetDefaultVariables(FVector::ZeroVector, 2000.f, 2500.f);
			EnemySpawner->UpdateWaveSpawningParams(InitialWave);
		}
	}
}
