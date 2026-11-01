// Gondos Daniel all rights reserved.


#include "Widgets/SimplePanels/GD_Widget_ServerListScreen.h"

#include "Input/CommonUIInputTypes.h"


void UGD_Widget_ServerListScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (RefreshAction)
	{
		//RefreshActionHandle = 
		RegisterUIActionBinding(FBindUIActionArgs(RefreshAction, true,
		                                          FSimpleDelegate::CreateUObject(
			                                          this, &ThisClass::BP_StartSearch)));
	}
}

void UGD_Widget_ServerListScreen::NativeOnActivated()
{
	Super::NativeOnActivated();
	BP_StartSearch();
}
