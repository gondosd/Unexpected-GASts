// Gondos Daniel all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Widget_ActivatableWidgetBase.generated.h"


class AFrontendPlayerController;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class UNEXPECTEDGASTS_API UWidget_ActivatableWidgetBase : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintPure)
	AFrontendPlayerController* GetOwningFrontendPlayerController();

private:
	TWeakObjectPtr<AFrontendPlayerController> CachedOwningFrontendPC;
};
