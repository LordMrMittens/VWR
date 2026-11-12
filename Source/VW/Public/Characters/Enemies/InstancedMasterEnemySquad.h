// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/BaseEnemy.h"
#include "InstancedMasterEnemySquad.generated.h"

class UInstancedStaticMeshComponent;
class UGunComponent;
class ABaseProjectile;
struct FInstanceStats;
struct FProjectileCollision;
/**
 * 
 */
USTRUCT()
struct FSpawnOffsetParams
{
	GENERATED_BODY()
public:
	float SpawnRotation{ 0.0f };
	float SpawnAltitude{ 0.0f };
	float RotationOffset{ 0.0f };
	float AltitudeOffset{ 0.0f };
};

UCLASS()
class VW_API AInstancedMasterEnemySquad : public ABaseEnemy
{
	GENERATED_BODY()

public:

	AInstancedMasterEnemySquad();

	UFUNCTION()
	virtual void GetHit(FProjectileCollision CollisionData) override;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UInstancedStaticMeshComponent> ISMAlienMesh;
	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<USceneComponent> EnemyRoot;
	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UGunComponent> GunComponent;

	UPROPERTY(EditAnywhere, Category = "InitialVariables")
	float StartingHeight{ 500.0f };

	UPROPERTY(EditAnywhere, Category = "InitialVariables")
	FRotator RotationalOffset{ 0.0f };

	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bDebugSpawn{ false };

	UPROPERTY(EditAnywhere, Category = "Debug")
	float DebugSpawnRotation{ 0.0f };

	UPROPERTY(EditAnywhere, Category = "Formation")
	int32 NumberOfRows{ 4 };
	UPROPERTY(EditAnywhere, Category = "Formation")
	int32 NumberOfColumns{ 6 };
	UPROPERTY(EditAnywhere, Category = "Formation")
	float HorizontalSpacing{ 2.0f };
	UPROPERTY(EditAnywhere, Category = "Formation")
	float VerticalSpacing{50.0f};

	UPROPERTY(EditAnywhere, Category = "Formation")
	float HorizontalMovementDuration{2.0f};
	UPROPERTY(EditAnywhere, Category = "Formation")
	float VerticalMovementDuration{0.5f};
	UPROPERTY(VisibleAnywhere, Category = "Formation")
	int32 AliveEnemiesInSquad{0};

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	TArray<FInstanceStats> PerInstanceStats;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FVector2D ShootingOffset{0.0f};
	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxTimeBetweenShots{ 6.0f};
	UPROPERTY(EditAnywhere, Category = "Combat")
	float MinTimeBetweenShots{ 3.0f};
	UPROPERTY(EditAnywhere, Category = "Combat")
	float AlienHealth{1.0f};
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<ABaseProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Combat")
	TWeakObjectPtr<ABaseProjectile> LastProjectile;
	FTimerHandle MovementTimerHandle;
	FTimerHandle ShootingTimerHandle;

	UFUNCTION()
	void SpawnInvaderISM(int32 Row, int32 Column);
	void CalculateInstanceOffset(int32 RowIndex, int32 ColumnIndex, FSpawnOffsetParams& OutSpawnParams);
	UFUNCTION()
	void StopAndMoveVertically();
	UFUNCTION()
	void StopAndMoveHorizontally();

	UFUNCTION()
	void Shoot();
};
