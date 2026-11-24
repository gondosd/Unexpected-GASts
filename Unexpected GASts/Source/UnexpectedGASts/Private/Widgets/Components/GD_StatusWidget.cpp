// Gondos Daniel all rights reserved.


#include "Widgets/Components/GD_StatusWidget.h"

#include "Characters/GD_BaseCharacter.h"

void UGD_StatusWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	//If there is no other Character given, the Local Player Character is the fallback
	if (!GAS_Character.IsValid())
		GAS_Character = Cast<AGD_BaseCharacter>(GetOwningPlayerPawn());

	if (IsASCInitialized())
		InitializeWidget(GAS_Character.Get()->GetAbilitySystemComponent(), GAS_Character.Get()->GetAttributeSet());
	else
		GAS_Character->OnASCInitialized.AddDynamic(this, &ThisClass::InitializeWidget);
}

void UGD_StatusWidget::InitializeWidget(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	//Do the initialization in the children
}

bool UGD_StatusWidget::IsASCInitialized() const
{
	return GAS_Character.Get()->GetAbilitySystemComponent() && GAS_Character.Get()->GetAttributeSet();
}
