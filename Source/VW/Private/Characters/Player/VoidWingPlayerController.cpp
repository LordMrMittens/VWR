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
	APawn* ControlledP = GetPawn();
	if(ControlledP && ControlledP->GetClass()->ImplementsInterface(UCharacterInterface::StaticClass()))
	{
		ControlledPawn = ControlledP;
	}
}

void AVoidWingPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AVoidWingPlayerController::Move);
	EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AVoidWingPlayerController::Shoot);
	
}

void AVoidWingPlayerController::Move(const FInputActionValue& InputActionValue)
{
	if (!ControlledPawn)
	{
		FindControlledPawn();
		return;
	}
	FVector2D MovementInputValue = InputActionValue.Get<FVector2D>();
	ControlledPawn->MoveCharacter(MovementInputValue.Y, MovementInputValue.X, GetWorld()->GetDeltaSeconds());

}

void AVoidWingPlayerController::Shoot()
{
	if (!ControlledPawn)
	{
		FindControlledPawn();
		return;
	}
	ControlledPawn->Shoot();
}
