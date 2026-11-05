#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseMover.h"
#include "Characters/Interfaces/CharacterInterface.h"
#include "PlayerCharacter.generated.h"

class UHealthComponent;
class UCapsuleComponent;
class UAutoSizeCamera;
class USpringArmComponent;
class UStaticMeshComponent;
class UBillboardComponent;
class ABaseProjectile;

UCLASS()
class VW_API APlayerCharacter : public ABaseMover, public ICharacterInterface
{
	GENERATED_BODY()

public:
	
	APlayerCharacter();

	virtual void UpdateHealth(int Value) override;

	UFUNCTION()
	virtual void Shoot() override;

	//Kept separate for now as players should never have a vertical direction input, overriding vertical direction with 0.0f unless this changes in the future
	virtual void Move(float HorizontalDir, float VerticalDir, float DeltaSeconds) override; //Base Move
	virtual void Move(float HorizontalDir, float VerticalDir) override; // Interface Move

	virtual float GetRotation() override;

protected:

	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, Category = "Default Components")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	UPROPERTY(EditAnywhere, Category = "Default Components")
	TObjectPtr <UStaticMeshComponent> MainMesh;
	UPROPERTY(EditAnywhere, Category = "Default Components")
	TObjectPtr <UStaticMeshComponent> GunMesh;
	UPROPERTY(EditAnywhere, Category = "Default Components")
	TObjectPtr <USpringArmComponent> SpringArm;
	UPROPERTY(EditAnywhere, Category = "Default Components")
	TObjectPtr <UAutoSizeCamera> Camera;
	UPROPERTY(EditAnywhere, Category = "Default Components")
	TObjectPtr <UBillboardComponent> GunSpawnPoint;
	UPROPERTY(EditAnywhere, Category = "Default Components")
	TObjectPtr <UHealthComponent> HealthComponent;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<ABaseProjectile> BulletClass;

	TWeakObjectPtr<ABaseProjectile> LatestBulletSpawned;

	UPROPERTY(EditAnywhere, Category = "Default Variables")
	float IntialAltitude{ 10.f };

	UFUNCTION()
	void DeathSequence();

	

};
