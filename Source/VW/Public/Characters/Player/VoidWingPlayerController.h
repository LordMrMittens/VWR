// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VoidWingPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ABaseMover;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class VW_API AVoidWingPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MovementAction;

	TWeakObjectPtr<ABaseMover> ControlledPawn;

	void Move(const FInputActionValue& InputActionValue);
	void FindControlledPawn();
};
