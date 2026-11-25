// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BaseItem.h"
#include "Components/SphereComponent.h"
#include "Characters/Interfaces/CharacterInterface.h"


ABaseItem::ABaseItem() 
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SphereComponent);
}

void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(CurrentHorzDirection, CurrentVertDirection, DeltaTime);
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	checkf(IsValid(SphereComponent), TEXT("BaseItem: No valid sphere component was detected"));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnItemOverlaps);

}

void ABaseItem::OnItemOverlaps(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor) || IsActorBeingDestroyed() || !IsValid(this)) return;
	//set collision settings so it doesnt collide with enemies or bullets
	//It should only collide with floor or player
	if (ICharacterInterface* HitActor = Cast<ICharacterInterface>(OtherActor)) // if colliding with player it gets picked up
	{
		//pick up item 
		//give item properties to player
		Destroy();
	}
	else {
		//if its not a player it must be the floor so it stops ticking
		SetActorTickEnabled(false);
	}
}

