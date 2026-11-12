// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Structs/ProjectileCollision.h"
#include "GunComponent.generated.h"

class ABaseProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VW_API UGunComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGunComponent();

	void Shoot(float Rotation, float Altitude, FVector2D Offset = FVector2D(0.0f));
	void Shoot(float Rotation, float Altitude, FVector SpawnPoint, FVector2D Offset = FVector2D(0.0f));

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere, Category = "Projectile Variables")
	TSubclassOf<ABaseProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Projectile Variables")
	FProjectileCollision ProjectileParams;

	UPROPERTY(EditAnywhere, Category = "Projectile Variables")
	float HorizontalDirection{0.0f};
	UPROPERTY(EditAnywhere, Category = "Projectile Variables")
	float VerticalDirection{ 1.0f };

	TWeakObjectPtr<ABaseProjectile> LastProjectile;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
