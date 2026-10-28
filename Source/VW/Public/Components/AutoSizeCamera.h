// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "AutoSizeCamera.generated.h"

/**
 * 
 */
UCLASS()
class VW_API UAutoSizeCamera : public UCameraComponent
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Default Settings")
	float TargetCameraWidth{ 2600.0f };

	UPROPERTY(VisibleAnywhere, Category = "Default Settings")
	float BaseScreenWidth{ 1920.f };
};
