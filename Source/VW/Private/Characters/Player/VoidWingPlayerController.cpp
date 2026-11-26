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
}

void AVoidWingPlayerController::FindControlledPawn(APawn* PossessedPawn)
{
	if(PossessedPawn && PossessedPawn->GetClass()->ImplementsInterface(UCharacterInterface::StaticClass()))
	{
		ControlledPawn = PossessedPawn;
	}
	checkf(ControlledPawn, TEXT("VoidWingPlayerController: Controlled Pawn Interface Not Found"));
}

void AVoidWingPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AVoidWingPlayerController::Move);
	EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AVoidWingPlayerController::Shoot);
	
}

void AVoidWingPlayerController::OnPossess(APawn* PossessedPawn)
{
	Super::OnPossess(PossessedPawn);
	FindControlledPawn(PossessedPawn);


	ControlledPawn->GetOnPlayerDeathDelegate()->AddUObject(this, &AVoidWingPlayerController::OnPlayerDied);
}

void AVoidWingPlayerController::OnPlayerDied(float LastRotation, float LastAltitude)
{
}

void AVoidWingPlayerController::Move(const FInputActionValue& InputActionValue)
{
	FVector2D MovementInputValue = InputActionValue.Get<FVector2D>();
	ControlledPawn->Move(MovementInputValue.Y, MovementInputValue.X);

}

void AVoidWingPlayerController::Shoot()
{
	ControlledPawn->Shoot();
}
