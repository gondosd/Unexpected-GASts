// Gondos Daniel all rights reserved.


#include "Widgets/Components/GD_AttributeWidget.h"

#include "AbilitySystemComponent.h"
#include "Characters/GD_BaseCharacter.h"

void UGD_AttributeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	checkf(AttributeMap.Value.IsValid() && AttributeMap.MaxValue.IsValid(), TEXT("AttributePair is not set"));
	
	//TEMP!!!!
	GAS_Character = Cast<AGD_BaseCharacter>(GetOwningPlayerPawn());

	const AGD_BaseCharacter* Character = GAS_Character.Get();
	const float AttributeValue = AttributeMap.Value.GetNumericValue(Character->GetAttributeSet());
	const float MaxAttributeValue = AttributeMap.MaxValue.GetNumericValue(Character->GetAttributeSet());

	BP_OnAttributeChange(AttributeValue, MaxAttributeValue, 0); //Init values

	BindAttributeChanges(Character, AttributeValue, MaxAttributeValue, AttributeMap.Value);
	BindAttributeChanges(Character, AttributeValue, MaxAttributeValue, AttributeMap.MaxValue);
}

void UGD_AttributeWidget::BindAttributeChanges(const AGD_BaseCharacter* Character, const float AttributeValue, const float MaxAttributeValue,
                                               const FGameplayAttribute& Attribute)
{
	Character->GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(Attribute).AddLambda(
		[this , AttributeValue, MaxAttributeValue](const FOnAttributeChangeData& AttributeChangeData)
		{
			BP_OnAttributeChange(AttributeValue, MaxAttributeValue, AttributeChangeData.OldValue);
		});
}
