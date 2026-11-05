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

	ABaseMover();

	UFUNCTION()
	virtual void Move(float HorizontalDir, float VerticalDir, float DeltaSeconds);

	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetInitialPosition(float InitialRotation, float InitialAltitude);


	UPROPERTY(EditAnywhere, Category = "Default Variables")
	float VerticalSpeed{ 0.0f };
	UPROPERTY(EditAnywhere, Category = "Default Variables")
	float HorizontalSpeed{ 5.0f };

	UPROPERTY(VisibleAnywhere, Category = "Movement Variables")
	float Altitude{ 0.0f };
	UPROPERTY(VisibleAnywhere, Category = "Movement Variables")
	float Rotation{ 0.0f };

	UPROPERTY(EditAnywhere, Category = "Default Variables")
	float DistanceFromCenter{ 2000.0f }; //MUST GET FROM GAME SETTINGS DELETE MESSAGE WHEN IMPLEMENTED

	const FVector CenterPoint{ 0.0f };
};
