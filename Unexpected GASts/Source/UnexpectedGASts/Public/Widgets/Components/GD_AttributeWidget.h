// Gondos Daniel all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GD_StatusWidget.h"
#include "GD_AttributeWidget.generated.h"


class AGD_BaseCharacter;
struct FGameplayAttribute;

USTRUCT(BlueprintType)
struct FGD_AttributePair
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttribute Value;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttribute MaxValue;
};

UCLASS()
class UNEXPECTEDGASTS_API UGD_AttributeWidget : public UGD_StatusWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	virtual void InitializeWidget(UAbilitySystemComponent* ASC, UAttributeSet* AS) override;
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Attribute Change"))
	void BP_OnAttributeChange(float NewValue, float NewMaxValue, float OldValue);

private:
	void BindAttributeChanges(UAbilitySystemComponent* ASC, const FGameplayAttribute& Attribute);
	void AttributePairChanged(float OldValue = 0.f);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Attributes", meta =(AllowPrivateAccess = true))
	FGD_AttributePair AttributeMap; //Value, MaxValue
};
