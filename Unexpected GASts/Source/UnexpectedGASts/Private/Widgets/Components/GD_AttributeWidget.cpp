// Gondos Daniel all rights reserved.


#include "Widgets/Components/GD_AttributeWidget.h"

#include "AbilitySystemComponent.h"
#include "Characters/GD_BaseCharacter.h"

void UGD_AttributeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	//TEMP!!!!
	GAS_Character = Cast<AGD_BaseCharacter>(GetOwningPlayerPawn());
	
	
	for (const TTuple<FGameplayAttribute, FGameplayAttribute>& AttributePair : AttributeMap)
	{
		const AGD_BaseCharacter* Character = GAS_Character.Get();
		const float AttributeValue = AttributePair.Key.GetNumericValue(Character->GetAttributeSet());
		const float MaxAttributeValue = AttributePair.Value.GetNumericValue(Character->GetAttributeSet());
		
		BP_OnAttributeChange(AttributeValue, MaxAttributeValue, 0); //Init values
		
		BindAttributeChanges(Character, AttributeValue, MaxAttributeValue,AttributePair.Key); //Watch Attribute Value
		BindAttributeChanges(Character, AttributeValue, MaxAttributeValue,AttributePair.Value); //Watch MaxAttribute Value
	}
}

void UGD_AttributeWidget::BindAttributeChanges(const AGD_BaseCharacter* Character, const float AttributeValue, const float MaxAttributeValue, const FGameplayAttribute& Attribute)
{
	Character->GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(Attribute).AddLambda(
		[this , AttributeValue, MaxAttributeValue](const FOnAttributeChangeData& AttributeChangeData)
		{
			BP_OnAttributeChange(AttributeValue, MaxAttributeValue, AttributeChangeData.OldValue);
		});
}
