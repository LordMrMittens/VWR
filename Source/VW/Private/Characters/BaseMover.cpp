// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseMover.h"
#include "Utils/MovementUtils.h"

// Sets default values
ABaseMover::ABaseMover()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseMover::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABaseMover::Move(float HorizontalDir, float VerticalDir, float DeltaSeconds)
{
	const FMovementStruct MovementParams{ Rotation,Altitude,DefaultHorzSpeed,DefaultVertSpeed,GetActorLocation(), FRotator::ZeroRotator, 
									HorizontalDir,VerticalDir,DistanceFromCenter, DeltaSeconds, CenterPoint };
	FMovementResult MovementResult;
	MovementUtils::CalculateMovement(MovementParams, MovementResult);
	Rotation = MovementResult.NewRotation;
	Altitude = MovementResult.NewAltitude;
	SetActorLocationAndRotation(MovementResult.UpdatedTransform.GetLocation(), MovementResult.UpdatedTransform.GetRotation(),false,nullptr,ETeleportType::TeleportPhysics);
}

void ABaseMover::SetInitialPosition(float InitialRotation, float InitialAltitude)
{
	Rotation = InitialRotation;
	Altitude = InitialAltitude;
	Move(0, 0, 0); // Deltatime might have to have a value over 0
}


// Called every frame
void ABaseMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(1, 0, DeltaTime);
}

