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
	void PlaySoundOnce(FName AudioTag);

	void StopAttachedLoopSound();
	void StopDetachedLoopSound();
protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:

	USoundBase* FindSound(FName AudioTag);

	UPROPERTY(EditAnywhere, Category = "Audio")
	TMap<FName, USoundBase*> AvailableAudios;
	UPROPERTY(EditAnywhere, Category = "Audio")
	float MaxDurationForDetachedLoops{ 5.0f };
	TObjectPtr<UAudioComponent> ActiveAttachedLoopComponent;
	TObjectPtr<UAudioComponent> ActiveDetachedLoopComponent;

	TObjectPtr<AActor> OwnerActor;
	
};
