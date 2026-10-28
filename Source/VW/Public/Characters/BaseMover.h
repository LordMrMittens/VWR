// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseMover.generated.h"

UCLASS()
class VW_API ABaseMover : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseMover();
	UFUNCTION()
	virtual void Move(float HorizontalDir, float VerticalDir, float DeltaSeconds);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Default Variables")
	float DistanceFromCenter{ 3000.0f };
	UPROPERTY(EditAnywhere, Category = "Default Variables")
	float DefaultVertSpeed{ 0.0f };
	UPROPERTY(EditAnywhere, Category = "Default Variables")
	float DefaultHorzSpeed{ 5.0f };
	
	const FVector CenterPoint {0.0f};

	UPROPERTY(VisibleAnywhere, Category = "Movement Variables")
	float Altitude{ 0.0f };
	UPROPERTY(VisibleAnywhere, Category = "Movement Variables")
	float Rotation{ 0.0f };

	void RotateAroundPoint(const FRotator RotationToAdd);
	float GetNormalisedRotation(float RawRotation);
	void SetLookAt();
	void SetInitialPosition(float InitialRotation, float InitialAltitude);
	float CalculateRotation(float HorizontalValue,float DeltaSeconds);
	float CalculateAltitude(float VerticalValue, float DeltaSeconds);
	void UpdatePosition(float IncomingRotation, float IncomingAltitude);
	FVector GetInstancedSMPosition(float InRotation, float InAltitude);



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
