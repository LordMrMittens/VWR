// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseMover.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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

void ABaseMover::RotateAroundPoint(const FRotator RotationToAdd) // This was a prototype, it used to put the actor at the center and then add an offset which seems inneficient.
{
	FVector CurrentLocation = GetActorLocation();
	FVector ToPointVector = CurrentLocation - CenterPoint;
	FVector NewLocation = CenterPoint + RotationToAdd.RotateVector(ToPointVector);
	SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
}

void ABaseMover::Move(float HorizontalDir, float VerticalDir, float DeltaSeconds)
{
	Rotation = CalculateRotation(HorizontalDir, DeltaSeconds);
	Altitude = CalculateAltitude(VerticalDir, DeltaSeconds);
	UpdatePosition(Rotation, Altitude);
	SetLookAt();
}

float ABaseMover::GetNormalisedRotation(float RawRotation)
{
	if (RawRotation > 0)
	{
		if (RawRotation > 360) 
		{ 
			return RawRotation - 360; 
		}
		return RawRotation;
	}
	return RawRotation + 360;
}

void ABaseMover::SetLookAt()
{
	FVector ActorLocation = GetActorLocation();
	FRotator LookAtRotation = (CenterPoint - ActorLocation).Rotation();
	SetActorRotation(LookAtRotation, ETeleportType::TeleportPhysics);
}

void ABaseMover::SetInitialPosition(float InitialRotation, float InitialAltitude)
{
	Rotation = InitialRotation;
	Altitude = InitialAltitude;
	Move(0, 0, 0); // Deltatime might have to have a value over 0
}

float ABaseMover::CalculateRotation(float HorizontalValue, float DeltaSeconds)
{

	float RawRotation = Rotation - ((HorizontalValue * DefaultHorzSpeed) * DeltaSeconds);
	return GetNormalisedRotation(RawRotation);
}

float ABaseMover::CalculateAltitude(float VerticalValue, float DeltaSeconds)
{
	return Altitude + ((VerticalValue * DefaultVertSpeed) * DeltaSeconds);
}

void ABaseMover::UpdatePosition(float IncomingRotation, float IncomingAltitude)
{

	FTransform RotTransform(FRotator(0.0f, IncomingRotation, 0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f));
	FMatrix PosMatrix = RotTransform.ToMatrixWithScale();
	FVector4 ResultVector = PosMatrix.TransformVector(FVector(0.0f, DistanceFromCenter, IncomingAltitude));
	SetActorLocation(FVector(CenterPoint + FVector(ResultVector)));
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

