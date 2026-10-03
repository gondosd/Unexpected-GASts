// Gondos Daniel all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FrontendPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNEXPECTEDGASTS_API AFrontendPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// ~ Begin APlayerController Interface
	virtual void OnPossess(APawn* aPawn) override;
	// ~ End APlayerController Interface
};
