// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AudioPlayerComponent.h"

void UAudioPlayerComponent::PlaySoundLoopingAttached(FName AudioTag)
{
	if (USoundBase* Sound = FindSound(AudioTag)) 
	{

	}
}

void UAudioPlayerComponent::PlaySoundLoopingDetached(FName AudioTag)
{
	if (USoundBase* Sound = FindSound(AudioTag))
	{

	}
}

void UAudioPlayerComponent::PlaySoundOnceAttached(FName AudioTag)
{
	if (USoundBase* Sound = FindSound(AudioTag))
	{

	}
}

void UAudioPlayerComponent::PlaySoundOnceDetached(FName AudioTag)
{
	if (USoundBase* Sound = FindSound(AudioTag))
	{

	}
}

USoundBase* UAudioPlayerComponent::FindSound(FName AudioTag)
{
	USoundBase* const* FoundSound = AvailableAudios.Find(AudioTag);
	return FoundSound ? *FoundSound : nullptr;
}
