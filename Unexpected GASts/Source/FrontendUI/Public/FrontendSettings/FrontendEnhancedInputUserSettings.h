// Gondos Daniel all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "FrontendEnhancedInputUserSettings.generated.h"


UCLASS(BlueprintType)
class FRONTENDUI_API UFrontendEnhancedPlayerMappableKeyProfile : public UEnhancedPlayerMappableKeyProfile
{
	GENERATED_BODY()

	friend class UFrontendEnhancedInputUserSettings;
};

UCLASS(config=GameUserSettings, DisplayName="Enhanced Input User Settings", Category="Enhanced Input|User Settings")
class FRONTENDUI_API UFrontendEnhancedInputUserSettings : public UEnhancedInputUserSettings
{
	GENERATED_BODY()

public:
	virtual void ResetAllPlayerKeysInRowForSlot(const FMapPlayerKeyArgs& InArgs, FGameplayTagContainer& FailureReason);
};
