// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AudioPlayerComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


void UAudioPlayerComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerActor = GetOwner();
}

void UAudioPlayerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	StopAttachedLoopSound();
}

void UAudioPlayerComponent::PlaySoundLoopingAttached(FName AudioTag)
{
	if (!IsValid(OwnerActor)) return;
	StopAttachedLoopSound();
	if (USoundBase* Sound = FindSound(AudioTag)) 
	{
		if (USceneComponent* Root = OwnerActor->GetRootComponent())
		{
			ActiveAttachedLoopComponent = UGameplayStatics::SpawnSoundAttached(Sound, Root);
		}
	}
}

void UAudioPlayerComponent::PlaySoundLoopingDetached(FName AudioTag)
{
	if (!IsValid(OwnerActor)) return;
	StopDetachedLoopSound();
	if (USoundBase* Sound = FindSound(AudioTag))
	{
		if (UAudioComponent* SpawnedLoop = UGameplayStatics::SpawnSoundAtLocation(this, Sound, OwnerActor->GetActorLocation()))
		{
			SpawnedLoop->bAutoDestroy = false;
			ActiveDetachedLoopComponent = SpawnedLoop;

			FTimerHandle SafetyTimer;
			TWeakObjectPtr<UAudioComponent> WeakLoop(SpawnedLoop);
			FTimerDelegate StopDelegate = FTimerDelegate::CreateWeakLambda(SpawnedLoop, [WeakLoop]()
				{
					if (UAudioComponent* Comp = WeakLoop.Get(); IsValid(Comp))
					{
						Comp->Stop();
						Comp->DestroyComponent();
					}
				});
			UWorld* World = GetWorld();
			checkf(World, TEXT("AudioPlayerComponent: Failed to get World when setting detached loop safety destruction timer"));
			World->GetTimerManager().SetTimer(SafetyTimer, StopDelegate, MaxDurationForDetachedLoops, false);
		}
	}
}

void UAudioPlayerComponent::PlaySoundOnce(FName AudioTag)
{
	if (!IsValid(OwnerActor)) return;
	if (USoundBase* Sound = FindSound(AudioTag))
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, OwnerActor->GetActorLocation());
	}
}

void UAudioPlayerComponent::StopAttachedLoopSound()
{
	if (!IsValid(ActiveAttachedLoopComponent)) return;
	ActiveAttachedLoopComponent->Stop();
	ActiveAttachedLoopComponent->DestroyComponent();
	ActiveAttachedLoopComponent = nullptr;
}

void UAudioPlayerComponent::StopDetachedLoopSound()
{
	if (!IsValid(ActiveDetachedLoopComponent)) return;
	ActiveDetachedLoopComponent->Stop();
	ActiveDetachedLoopComponent->DestroyComponent();
	ActiveDetachedLoopComponent = nullptr;
}

USoundBase* UAudioPlayerComponent::FindSound(FName AudioTag)
{
	USoundBase* const* FoundSound = AvailableAudios.Find(AudioTag);
	return FoundSound ? *FoundSound : nullptr;
}
