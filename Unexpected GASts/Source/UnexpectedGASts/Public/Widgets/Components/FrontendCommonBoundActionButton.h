// Gondos Daniel all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Input/CommonBoundActionButton.h"
#include "FrontendCommonBoundActionButton.generated.h"

/**
 * 
 */
UCLASS()
class UNEXPECTEDGASTS_API UFrontendCommonBoundActionButton : public UCommonBoundActionButton
{
	GENERATED_BODY()

protected:
	virtual void NativeOnHovered() override;
};
