// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/InstancedMasterEnemySquad.h"
#include "Utils/MovementUtils.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Structs/InstanceStats.h"

AInstancedMasterEnemySquad::AInstancedMasterEnemySquad()
{
	EnemyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(EnemyRoot);
	ISMAlienMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ISM"));
	ISMAlienMesh->SetupAttachment(EnemyRoot);
}

void AInstancedMasterEnemySquad::BeginPlay()
{
	Super::BeginPlay();
	Move(0, 0, 0.1f);
	float SpawnRotation = bDebugSpawn ? DebugSpawnRotation : FMath::RandRange(0, 360);
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
	StopAndMoveHorizontally();
}

void AInstancedMasterEnemySquad::SpawnInvaderISM(int32 Row, int32 Column)
{
	FSpawnOffsetParams Params;
	CalculateInstanceOffset(Row, Column, Params);
	
	FVector SpawnLocation = MovementUtils::CalculateUpdatedPosition(Params.SpawnRotation, Params.SpawnAltitude, DistanceFromCenter, CenterPoint);
	FRotator SpawnLookAt = GetActorRotation() + RotationalOffset; // Can edit Mesh so this is unnecesary
	FTransform SpawnTransform (SpawnLookAt, SpawnLocation, FVector{ 1.0f });
	int32 InstanceIndex = ISMAlienMesh->AddInstance(SpawnTransform, false);
	int32 StatsIndex = PerInstanceStats.Emplace( FInstanceStats{ InstanceIndex,AlienHealth, false, FVector2D(Params.RotationOffset, Params.AltitudeOffset) });
	AliveEnemies.AddUnique(StatsIndex);
}

void AInstancedMasterEnemySquad::CalculateInstanceOffset(int32 RowIndex, int32 ColumnIndex, FSpawnOffsetParams& OutSpawnParams)
{
	OutSpawnParams.RotationOffset = HorizontalSpacing * ColumnIndex;
	OutSpawnParams.AltitudeOffset = VerticalSpacing * RowIndex;
	OutSpawnParams.SpawnRotation = MovementUtils::GetNormalisedRotation(Rotation + OutSpawnParams.RotationOffset);
	OutSpawnParams.SpawnAltitude = Altitude + OutSpawnParams.AltitudeOffset;// Why not -> Altitude + Params.AltitudeOffset;
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
