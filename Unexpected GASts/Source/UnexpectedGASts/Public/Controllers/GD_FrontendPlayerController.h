// Gondos Daniel all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GD_PlayerControllerBase.h"
#include "GD_FrontendPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNEXPECTEDGASTS_API AGD_FrontendPlayerController : public AGD_PlayerControllerBase
{
	GENERATED_BODY()

protected:
	// ~ Begin APlayerController Interface
	virtual void OnPossess(APawn* aPawn) override;
	// ~ End APlayerController Interface
};
