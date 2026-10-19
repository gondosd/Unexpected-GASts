// Gondos Daniel all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/FrontendLoadingScreenInterface.h"
#include "GD_PlayerControllerBase.generated.h"


class UInputMappingContext;

UCLASS(Abstract)
class UNEXPECTEDGASTS_API AGD_PlayerControllerBase : public APlayerController , public IFrontendLoadingScreenInterface
{
	GENERATED_BODY()
	
public:
	virtual void OnLoadingScreenDeactivated_Implementation() override;

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "GD|Input")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContextsToRegister;
	
	UPROPERTY(EditDefaultsOnly, Category = "GD|Input")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContextsToAdd;
};
