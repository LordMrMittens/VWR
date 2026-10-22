// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseMover.h"
#include "BaseEnemy.generated.h"

/**
 * 
 */
UCLASS() //THIS CLASS IS DEPRECATED, REPLICATING FOR SYSTEMS TEMPORARILY
class VW_API ABaseEnemy : public ABaseMover
{
	GENERATED_BODY()

protected:

	float CurrentHorzDirection{ 0.0f };
	float CurrentVerticalDirection{ 0.0f };

public:

	virtual void Tick(float DeltaTime) override;
	
};
