// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/MovementUtils.h"


namespace MovementUtils
{
   const FMovementResult CalculateMovement(const FMovementStruct& MovementParams)
    {
        FMovementResult Result;
        FRotator UpdatedLookAt = GetUpdatedLookAt(MovementParams.CurrentLocation, MovementParams.CenterPoint);
        Result.NewRotation = CalculateRotation(MovementParams.CurrentRotation, MovementParams.HorizontalSpeed, MovementParams.HorizontalDirection, MovementParams.DeltaSeconds);
        Result.NewAltitude = CalculateAltitude(MovementParams.CurrentAltitude, MovementParams.VerticalSpeed, MovementParams.VerticalDirection, MovementParams.DeltaSeconds);
        Result.UpdatedTransform = FTransform(UpdatedLookAt, CalculateUpdatedPosition(Result.NewRotation, Result.NewAltitude, MovementParams.DistanceFromCenter, MovementParams.CenterPoint));
        return Result;
    }

    float GetNormalisedRotation(float RawRotation)
    {
        return FMath::Fmod(RawRotation, 360.0f);
     /*   if (RawRotation > 0)
        {
            if (RawRotation > 360)
            {
                return RawRotation - 360;
            }
            return RawRotation;
        }
        return RawRotation + 360;*/
    }

    FRotator GetUpdatedLookAt(FVector CurrentLocation, FVector CenterPoint)
    {
        FVector LookAt(FVector(CenterPoint.X, CenterPoint.Y, CurrentLocation.Z) - CurrentLocation);
        return LookAt.Rotation();
    }

    float CalculateRotation(float CurrentRotation, float HorizontalSpeed, float HorizontalDirection, float DeltaSeconds)
    {
        float RawRotation = CurrentRotation - ((HorizontalDirection * HorizontalSpeed) * DeltaSeconds);
        return GetNormalisedRotation(RawRotation);
    }

    float CalculateAltitude(float CurrentAltitude, float VerticalSpeed, float VerticalDirection, float DeltaSeconds)
    {
        return CurrentAltitude + ((VerticalDirection * VerticalSpeed) * DeltaSeconds);
    }

    FVector MovementUtils::CalculateUpdatedPosition(float IncomingRotation, float IncomingAltitude, float DistanceFromCenter, FVector CenterPoint)
    {
        FTransform RotTransform(FRotator(0.0f, IncomingRotation, 0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f));
        FMatrix PosMatrix = RotTransform.ToMatrixWithScale();
        FVector4 ResultVector = PosMatrix.TransformVector(FVector(0.0f, DistanceFromCenter, IncomingAltitude));
        return FVector(CenterPoint + FVector(ResultVector));
    }
}