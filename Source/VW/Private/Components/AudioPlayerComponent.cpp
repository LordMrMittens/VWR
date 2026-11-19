// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AudioPlayerComponent.h"

void UAudioPlayerComponent::PlaySoundLoopingAttached(FName AudioTag)
{
	if (USoundBase* const* FoundSound = AvailableAudios.Find(AudioTag))
	{

	}
}

void UAudioPlayerComponent::PlaySoundLoopingDetached(FName AudioTag)
{
	if (USoundBase* const* FoundSound = AvailableAudios.Find(AudioTag))
	{

	}
}

void UAudioPlayerComponent::PlaySoundOnceAttached(FName AudioTag)
{
	if (USoundBase* const* FoundSound = AvailableAudios.Find(AudioTag))
	{

	}
}

void UAudioPlayerComponent::PlaySoundOnceDetached(FName AudioTag)
{
	if (USoundBase* const* FoundSound = AvailableAudios.Find(AudioTag))
	{

	}
}
