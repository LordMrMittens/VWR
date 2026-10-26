// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/VoidWingPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Characters/BaseMover.h"

void AVoidWingPlayerController::BeginPlay()
{
	Super::BeginPlay();
	checkf(InputMappingContext, TEXT("AVoidWingPlayerController: No InputMappingContext found"));
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
	FindControlledPawn();
}

void AVoidWingPlayerController::FindControlledPawn()
{
	ControlledPawn = GetPawn<ABaseMover>();
}

void AVoidWingPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AVoidWingPlayerController::Move);
	
}

void AVoidWingPlayerController::Move(const FInputActionValue& InputActionValue)
{
	if (!ControlledPawn.IsValid())
	{
		FindControlledPawn();
		return;
	}
	FVector2D MovementInputValue = InputActionValue.Get<FVector2D>();
	ControlledPawn->Move(MovementInputValue.Y, MovementInputValue.X, GetWorld()->GetDeltaSeconds());

}
