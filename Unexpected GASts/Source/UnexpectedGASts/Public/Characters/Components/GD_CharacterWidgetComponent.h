// Gondos Daniel all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GD_CharacterWidgetComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNEXPECTEDGASTS_API UGD_CharacterWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UGD_CharacterWidgetComponent();

	virtual void InitWidget() override;
};
