// Fill out your copyright notice in the Description page of Project Settings.


#include "Ambience/Graphics/RotatingCard.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/MovementUtils.h"

// Sets default values
ARotatingCard::ARotatingCard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootC = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	SetRootComponent(RootC);
	Card = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FogCard"));
	Card->SetupAttachment(RootC);
}

// Called when the game starts or when spawned
void ARotatingCard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotatingCard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerCharacter) {
		AssignPlayerCharacter();
		return;
	}
	RotateWithPlayer();
}

void ARotatingCard::RotateWithPlayer()
{
	float DesiredRotation = PlayerCharacter->GetRotation();
	FRotator UpdatedLookAt = MovementUtils::GetUpdatedLookAt(GetActorLocation(), FVector(0));
	FVector UpdatedPosition = MovementUtils::CalculateUpdatedPosition(DesiredRotation, DistanceFromCenter, 0.0f, CenterPoint);
	SetActorLocationAndRotation(UpdatedPosition, UpdatedLookAt, false, nullptr, ETeleportType::TeleportPhysics);
}

void ARotatingCard::AssignPlayerCharacter()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this,0);
	if (PlayerPawn && PlayerPawn->GetClass()->ImplementsInterface(UCharacterInterface::StaticClass())) {

		PlayerCharacter = PlayerPawn;
	}
}

