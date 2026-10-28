// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AutoSizeCamera.h"
#include "GameFramework/GameUserSettings.h"


void UAutoSizeCamera::BeginPlay()
{
	Super::BeginPlay();

	FIntPoint ScreenRes = UGameUserSettings::GetGameUserSettings()->GetScreenResolution();
	float CurrentOrthoWidth = (static_cast<float>(ScreenRes.X) / BaseScreenWidth) * TargetCameraWidth;
	SetOrthoWidth(CurrentOrthoWidth);
}
