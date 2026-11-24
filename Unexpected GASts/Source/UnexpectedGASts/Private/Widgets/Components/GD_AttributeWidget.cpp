// Gondos Daniel all rights reserved.


#include "Widgets/Components/GD_AttributeWidget.h"

#include "AbilitySystemComponent.h"
#include "Characters/GD_BaseCharacter.h"

void UGD_AttributeWidget::NativeConstruct()
{
	checkf(AttributeMap.Value.IsValid() && AttributeMap.MaxValue.IsValid(), TEXT("AttributePair is not set"));
	Super::NativeConstruct();
}

void UGD_AttributeWidget::InitializeWidget(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AttributePairChanged(); //Init

	BindAttributeChanges(ASC, AttributeMap.Value);
	BindAttributeChanges(ASC, AttributeMap.MaxValue);
}

void UGD_AttributeWidget::BindAttributeChanges(UAbilitySystemComponent* ASC, const FGameplayAttribute& Attribute)
{
	ASC->GetGameplayAttributeValueChangeDelegate(Attribute).AddLambda(
		[this ](const FOnAttributeChangeData& AttributeChangeData)
		{
			AttributePairChanged(AttributeChangeData.OldValue);
		});
}

void UGD_AttributeWidget::AttributePairChanged(const float OldValue)
{
	const float InitAttributeValue = AttributeMap.Value.GetNumericValue(GAS_Character.Get()->GetAttributeSet());
	const float InitMaxAttributeValue = AttributeMap.MaxValue.GetNumericValue(GAS_Character.Get()->GetAttributeSet());
	BP_OnAttributeChange(InitAttributeValue, InitMaxAttributeValue, OldValue);
}
