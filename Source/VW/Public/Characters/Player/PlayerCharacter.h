#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseMover.h"
#include "Characters/Interfaces/CharacterInterface.h"
#include "PlayerCharacter.generated.h"

class UHealthComponent;
class UCapsuleComponent;
class UCameraComponent;
class USpringArmComponent;
class UStaticMeshComponent;
class UBillboardComponent;

UCLASS()
class VW_API APlayerCharacter : public ABaseMover, public ICharacterInterface
{
	GENERATED_BODY()

public:
	
	APlayerCharacter();

	virtual void UpdateHealth(int Value) override;

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
	TObjectPtr <UCameraComponent> Camera;
	UPROPERTY(EditAnywhere, Category = "Default Components")
	TObjectPtr <UBillboardComponent> GunSpawnPoint;
	UPROPERTY(EditAnywhere, Category = "Default Components")
	TObjectPtr <UHealthComponent> HealthComponent;

	UFUNCTION()
	void DeathSequence();

};
