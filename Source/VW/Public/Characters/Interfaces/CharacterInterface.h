// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterInterface.generated.h"

struct FProjectileCollision;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VW_API ICharacterInterface
{
	GENERATED_BODY()

public:
	
	virtual void UpdateHealth(int Value);

	virtual void Die();

	virtual void GetHit(FProjectileCollision CollisionData);
	//UFUNCTION(BlueprintNativeEvent)
	virtual void Shoot();

	virtual void MoveCharacter(float HorizontalDir, float VerticalDir, float DeltaSeconds);
};
