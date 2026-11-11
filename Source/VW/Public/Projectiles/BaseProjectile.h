// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseMover.h"
#include "Structs/ProjectileCollision.h"
#include "BaseProjectile.generated.h"

class UStaticMeshComponent;
/**
 * 
 */
UCLASS()
class VW_API ABaseProjectile : public ABaseMover
{
	GENERATED_BODY()

public:
	ABaseProjectile();

	void SetupProjectile(float StartingRotation, float StartingAltitude, float HorzDirection, float VertDirection);

	UFUNCTION()
	void OnProjectileOverlaps(AActor* OverlappedActor, AActor* OtherActor);

protected:
	virtual void BeginPlay() override;
	
private:

	UPROPERTY(EditAnywhere, Category = "Default Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, Category = "Projectile Stats")
	FProjectileCollision ProjectileData;

	float HorizontalDirection{ 0.0f };
	float VerticalDirection{ 0.0f };
public:

	virtual void Tick(float DeltaTime) override;

};
