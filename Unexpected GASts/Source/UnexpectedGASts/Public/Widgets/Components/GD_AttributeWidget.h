// Gondos Daniel all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayEffectTypes.h"
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
class UNEXPECTEDGASTS_API UGD_AttributeWidget : public UCommonUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Attribute Change"))
	void BP_OnAttributeChange(float NewValue, float NewMaxValue, float OldValue);

private:
	void BindAttributeChanges(const AGD_BaseCharacter* Character, float AttributeValue, float MaxAttributeValue, const FGameplayAttribute& Attribute);
	
	TWeakObjectPtr<AGD_BaseCharacter> GAS_Character; //We can get the attributes from it, what to follow
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Attributes", meta =(AllowPrivateAccess = true))
	FGD_AttributePair AttributeMap; //Value, MaxValue
};
