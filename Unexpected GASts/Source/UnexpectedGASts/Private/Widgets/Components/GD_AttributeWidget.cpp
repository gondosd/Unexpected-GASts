// Gondos Daniel all rights reserved.


#include "Widgets/Components/GD_AttributeWidget.h"

#include "AbilitySystemComponent.h"
#include "Characters/GD_BaseCharacter.h"

void UGD_AttributeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	checkf(AttributeMap.Value.IsValid() && AttributeMap.MaxValue.IsValid(), TEXT("AttributePair is not set"));
	
	//If there is no other Character given, the Local Player Character is the fallback
	if (!GAS_Character.IsValid())
		GAS_Character = Cast<AGD_BaseCharacter>(GetOwningPlayerPawn());

	if (IsASCInitialized())
		InitializeWidget(GAS_Character.Get()->GetAbilitySystemComponent(), GAS_Character.Get()->GetAttributeSet());
	else
		GAS_Character->OnASCInitialized.AddDynamic(this, &ThisClass::InitializeWidget);
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

bool UGD_AttributeWidget::IsASCInitialized() const
{
	return GAS_Character.Get()->GetAbilitySystemComponent() && GAS_Character.Get()->GetAttributeSet();
}
