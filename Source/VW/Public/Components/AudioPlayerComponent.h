// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AudioPlayerComponent.generated.h"

/**
 * 
 */
UCLASS()
class VW_API UAudioPlayerComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	void PlaySoundLoopingAttached(FName AudioTag);
	void PlaySoundLoopingDetached(FName AudioTag);
	void PlaySoundOnceAttached(FName AudioTag);
	void PlaySoundOnceDetached(FName AudioTag);
private:

	USoundBase* FindSound(FName AudioTag);

	UPROPERTY(EditAnywhere, Category = "Audio")
	TMap<FName, USoundBase*> AvailableAudios;

	TObjectPtr<UAudioComponent> ActiveAttachedLoopComponent;
	
};
