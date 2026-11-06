// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/BaseEnemy.h"
#include "InstancedMasterEnemySquad.generated.h"

class UInstancedStaticMeshComponent;
class ABaseProjectile;
struct FInstanceStats;
/**
 * 
 */
UCLASS()
class VW_API AInstancedMasterEnemySquad : public ABaseEnemy
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UInstancedStaticMeshComponent> ISMAlienMesh;

	UPROPERTY(EditAnywhere, Category = "Formation")
	int16 NumberOfRows{ 4 };
	UPROPERTY(EditAnywhere, Category = "Formation")
	int16 NumberOfColumns{ 6 };
	UPROPERTY(EditAnywhere, Category = "Formation")
	float HorizontalSpacing{ 2.0f };
	UPROPERTY(EditAnywhere, Category = "Formation")
	float VerticalSpacing{50.0f};
	UPROPERTY(VisibleAnywhere, Category = "Formation")
	TArray<int32> AliveEnemies;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	TArray<FInstanceStats> PerInstanceStats;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FVector ShootingOffset;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxTimeBetweenShots;
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<ABaseProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Combat")
	TWeakObjectPtr<ABaseProjectile> LastProjectile;
};
