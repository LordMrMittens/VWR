// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseMover.h"
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
	
private:

	UPROPERTY(EditAnywhere, Category = "Default Components")
	TObjectPtr<UStaticMeshComponent> Mesh;
	float HorizontalDirection{ 0.0f };
	float VerticalDirection{ 0.0f };
public:

	virtual void Tick(float DeltaTime) override;

};
