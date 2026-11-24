// Gondos Daniel all rights reserved.


#include "Characters/Components/GD_CharacterWidgetComponent.h"

#include "Blueprint/WidgetTree.h"
#include "Characters/GD_BaseCharacter.h"
#include "Widgets/Components/GD_StatusWidget.h"

UGD_CharacterWidgetComponent::UGD_CharacterWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGD_CharacterWidgetComponent::InitWidget()
{
	if (!GetWidget() && WidgetClass && GetWorld() && !GetWorld()->IsNetMode(NM_DedicatedServer))
	{
		UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		
		if (UGD_StatusWidget* AttributeWidget = Cast<UGD_StatusWidget>(NewWidget))
		{
			// has to be injected before NativeConstruct runs
			AttributeWidget->SetGAS_Character(Cast<AGD_BaseCharacter>(GetOwner()));
		}
		else
		{
			//loop over all children on the owned widget, search for Attribute widgets to inject reference before NativeConstruct runs
			NewWidget->WidgetTree->ForEachWidget([this](UWidget* ChildWidget)
			{
				if (UGD_StatusWidget* AttributeWidget = Cast<UGD_StatusWidget>(ChildWidget))
				{
					AttributeWidget->SetGAS_Character(Cast<AGD_BaseCharacter>(GetOwner()));
				}
			});
		}

		SetWidget(NewWidget);
	}

	Super::InitWidget();
}
