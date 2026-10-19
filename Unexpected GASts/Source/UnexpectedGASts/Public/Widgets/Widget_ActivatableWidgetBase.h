// Gondos Daniel all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Widget_ActivatableWidgetBase.generated.h"


class AGD_FrontendPlayerController;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class UNEXPECTEDGASTS_API UWidget_ActivatableWidgetBase : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintPure)
	AGD_FrontendPlayerController* GetOwningFrontendPlayerController();

private:
	TWeakObjectPtr<AGD_FrontendPlayerController> CachedOwningFrontendPC;
};
