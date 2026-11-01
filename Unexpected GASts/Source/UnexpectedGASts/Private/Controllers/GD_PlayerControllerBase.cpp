// Gondos Daniel all rights reserved.


#include "Controllers/GD_PlayerControllerBase.h"

#include "EnhancedInputSubsystems.h"
#include "FontendFunctionLibrary.h"
#include "GD_GameplayTags.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/FrontendUISubsystem.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "Widgets/Widget_PrimaryLayout.h"
#include "Widgets/SimplePanels/Widget_CreditsScreen.h"

void AGD_PlayerControllerBase::OnLoadingScreenDeactivated_Implementation()
{
	IFrontendLoadingScreenInterface::OnLoadingScreenDeactivated_Implementation();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(InputSubsystem)) return;

	for (TObjectPtr<UInputMappingContext> Context : InputMappingContextsToRegister)
	{
		InputSubsystem->GetUserSettings()->RegisterInputMappingContext(Context);
	}

	for (TObjectPtr<UInputMappingContext> Context : InputMappingContextsToAdd)
	{
		InputSubsystem->AddMappingContext(Context, 1);
	}

	if (UWidget_PrimaryLayout* PrimaryLayoutWidget = CreateWidget<UWidget_PrimaryLayout>(
		this, UFontendFunctionLibrary::GetPrimaryLayoutWidgetClass().LoadSynchronous()))
	{
		PrimaryLayoutWidget->AddToViewport();
		UFrontendUISubsystem::Get(this)->RegisterCreatedPrimaryLayoutWidget(PrimaryLayoutWidget);
	}

	//Set Focus to Game Viewport
	FSlateApplication::Get().SetAllUserFocusToGameViewport();
}
