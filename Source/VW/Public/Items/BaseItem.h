// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseMover.h"
#include "BaseItem.generated.h"

class USphereComponent;
class UStaticMeshComponent;
/**
 * 
 */
UCLASS()
class VW_API ABaseItem : public ABaseMover
{
	GENERATED_BODY()


public:
	ABaseItem();

	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Default Variables")
	float CurrentHorzDirection{ 0.0f };
	UPROPERTY(EditAnywhere, Category = "Default Variables")
	float CurrentVertDirection{ -1.0f };

private:

	UPROPERTY(EditAnywhere, Category = "Default Components")
	TObjectPtr<USphereComponent> SphereComponent;
	UPROPERTY(EditAnywhere, Category = "Default Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UFUNCTION()
	void OnItemOverlaps(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
