// Gondos Daniel all rights reserved.


#include "Controllers/GD_PlayerControllerBase.h"

#include "EnhancedInputSubsystems.h"
#include "UserSettings/EnhancedInputUserSettings.h"

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
}
