// Gondos Daniel all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GD_StatusWidget.generated.h"


class UAttributeSet;
class UAbilitySystemComponent;
class AGD_BaseCharacter;

UCLASS()
class UNEXPECTEDGASTS_API UGD_StatusWidget : public UCommonUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void InitializeWidget(UAbilitySystemComponent* ASC, UAttributeSet* AS);

	bool IsASCInitialized() const;

public:
	FORCEINLINE void SetGAS_Character(const TWeakObjectPtr<AGD_BaseCharacter>& InGASCharacter) { GAS_Character = InGASCharacter; }

protected:
	TWeakObjectPtr<AGD_BaseCharacter> GAS_Character; //We can get the attributes from it, what to follow
};
