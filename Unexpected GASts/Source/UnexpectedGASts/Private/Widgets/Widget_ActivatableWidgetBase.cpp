// Gondos Daniel all rights reserved.


#include "Widgets/Widget_ActivatableWidgetBase.h"
#include "Controllers/FrontendPlayerController.h"

AFrontendPlayerController* UWidget_ActivatableWidgetBase::GetOwningFrontendPlayerController()
{
	if (!CachedOwningFrontendPC.IsValid())
	{
		CachedOwningFrontendPC = GetOwningPlayer<AFrontendPlayerController>();
	}

	return CachedOwningFrontendPC.IsValid() ? CachedOwningFrontendPC.Get() : nullptr;
}
