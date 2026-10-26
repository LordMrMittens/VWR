// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/BaseEnemy.h"

void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(CurrentHorzDirection, CurrentVerticalDirection, DeltaTime);
}
