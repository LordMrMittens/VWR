#pragma once

#include "CoreMinimal.h"
#include "InstanceStats.generated.h"

USTRUCT()
struct FInstanceStats
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, Category = "Stats")
	int Index{ 0 };
	UPROPERTY(EditAnywhere, Category = "Stats")
	float Health { 1.0f }; //May be int
	UPROPERTY(VisibleAnywhere, Category = "Stats")
	bool bIsDead{ false };
	UPROPERTY(VisibleAnywhere, Category = "Stats")
	FVector Offset{ 0.0f };



};
