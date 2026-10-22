// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "ProjectileCollision.generated.h"

/**
 * 
 */
UCLASS()
class VW_API UProjectileCollision : public UStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Projectile Values")
	FVector Location{ 0.0f };
	UPROPERTY(EditAnywhere, Category = "Projectile Values")
	float DamageRadius{ 10.0f };
	UPROPERTY(EditAnywhere, Category = "Projectile Values")
	int Damage{ 1 };
	
};
