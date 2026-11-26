#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameModeInterface.generated.h"

UINTERFACE(MinimalAPI)
class UGameModeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class VW_API IGameModeInterface
{
	GENERATED_BODY()

public:

	virtual void OnPlayerDeath (float LastRotation, float LastAltitude);

};

