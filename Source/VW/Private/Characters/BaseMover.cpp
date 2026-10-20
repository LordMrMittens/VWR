// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseMover.h"

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

void ABaseMover::RotateAroundPoint(const FRotator RotationToAdd)
{
}

void ABaseMover::Move(float Horizontal, float Vertical)
{
}

float ABaseMover::GetNormalisedRotation(float RawRotation)
{
	return 0.0f;
}

void ABaseMover::SetLookAt()
{
}

void ABaseMover::SetInitialPosition(float InitialRotation)
{
}

float ABaseMover::CalculateRotation(float HorizontalValue)
{
	return 0.0f;
}

float ABaseMover::CalculateAltitude(float VerticalValue)
{
	return 0.0f;
}

void ABaseMover::UpdatePosition(float IncomingRotation, float IncomingAltitude)
{
}

FVector ABaseMover::GetInstancedSMPosition(float InRotation, float InAltitude)
{
	return FVector();
}

// Called every frame
void ABaseMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

