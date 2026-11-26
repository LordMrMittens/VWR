// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/VoidWingGameMode.h"
#include "Utils/MovementUtils.h"
#include "Characters/Player/PlayerCharacter.h"
#include "Gameplay/EnemySpawner.h"

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

void AVoidWingGameMode::OnPlayerDeath(float LastRotation, float LastAltitude)
{
	FTimerDelegate RespawnDelegate = FTimerDelegate::CreateUObject(
		this,
		&AVoidWingGameMode::RespawnPlayer,
		LastRotation,
		LastAltitude
	);

	GetWorldTimerManager().SetTimer(PlayerRespawnTimerHandle, RespawnDelegate, RespawnDelay, false);
}

void AVoidWingGameMode::RespawnPlayer(float LastRotation, float LastAltitude)
{
	FTransform DeathTransform = MovementUtils::CalculateInitialTransform(LastRotation, LastAltitude, 2000, FVector::ZeroVector);
	APlayerCharacter* PlayerActor = GetWorld()->SpawnActorDeferred<APlayerCharacter>(DefaultPawnClass, DeathTransform);

	if (!IsValid(PlayerActor)) return;

	PlayerActor->UpdateInitialPositionVariable(LastRotation, LastAltitude);
	PlayerActor->FinishSpawning(DeathTransform);
	//do we need to possess
}


