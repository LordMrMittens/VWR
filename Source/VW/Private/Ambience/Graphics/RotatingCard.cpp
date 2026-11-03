// Fill out your copyright notice in the Description page of Project Settings.


#include "Ambience/Graphics/RotatingCard.h"
#include "Utils/MovementUtils.h"

// Sets default values
ARotatingCard::ARotatingCard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

