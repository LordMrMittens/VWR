// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


struct FMovementStruct {
	float CurrentRotation{ 0 };
	float CurrentAltitude{ 0 };
	float HorizontalSpeed{ 0 };
	float VerticalSpeed{ 0 };
	FVector CurrentLocation{ 0 };
	float HorizontalDirection{ 0 };
	float VerticalDirection{ 0 };
	float DistanceFromCenter{ 0 };
	float DeltaSeconds{ 0 };
	FVector CenterPoint{ 0 };
};

struct FMovementResult 
{
	FTransform UpdatedTransform;
	float NewRotation;
	float NewAltitude;
};
/**
 * 
 */
namespace MovementUtils
{

	//void CalculateMovement(const FMovementStruct& MovementParams, FMovementResult& OutMovementResult);
	const FMovementResult CalculateMovement(const FMovementStruct& MovementParams);
	float GetNormalisedRotation(float RawRotation);
	float CalculateRotation(float CurrentRotation, float HorizontalSpeed, float HorizontalValue, float DeltaSeconds);
	float CalculateAltitude(float CurrentAltitude, float VerticalSpeed, float VerticalDirection, float DeltaSeconds);
	FRotator GetUpdatedLookAt(FVector CurrentLocation, FVector CenterPoint);
	FVector CalculateUpdatedPosition(float IncomingRotation, float DistanceFromCenter, float IncomingAltitude, FVector CenterPoint);
	FVector GetInstancedSMPosition(float InRotation, float InAltitude);
	
};
