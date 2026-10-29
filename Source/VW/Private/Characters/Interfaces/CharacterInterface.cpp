// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Interfaces/CharacterInterface.h"
#include "Structs/ProjectileCollision.h"

// Add default functionality here for any ICharacterInterface functions that are not pure virtual.

void ICharacterInterface::UpdateHealth(int Value)
{
}

void ICharacterInterface::Die()
{
}

void ICharacterInterface::GetHit(FProjectileCollision CollisionData)
{
}

//void ICharacterInterface::Shoot()
//{
//}

void ICharacterInterface::MoveCharacter(float HorizontalDir, float VerticalDir, float DeltaSeconds)
{
}
