// Gondos Daniel all rights reserved.


#include "Characters/Components/GD_CharacterWidgetComponent.h"

#include "Characters/GD_BaseCharacter.h"
#include "Widgets/Components/GD_AttributeWidget.h"

UGD_CharacterWidgetComponent::UGD_CharacterWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGD_CharacterWidgetComponent::InitWidget()
{
	if (!GetWidget() && WidgetClass && GetWorld() && !GetWorld()->IsNetMode(NM_DedicatedServer))
	{
		UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);

		if (UGD_AttributeWidget* AttrWidget = Cast<UGD_AttributeWidget>(NewWidget))
		{
			// has to be injected before NativeConstruct runs
			AttrWidget->GAS_Character = Cast<AGD_BaseCharacter>(GetOwner()); //TODO: run through all widgets in the widget tree to do this
		}

		SetWidget(NewWidget);
	}
	
	Super::InitWidget();
}


