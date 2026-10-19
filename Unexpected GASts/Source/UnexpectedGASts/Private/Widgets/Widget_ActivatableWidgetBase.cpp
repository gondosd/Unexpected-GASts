// Gondos Daniel all rights reserved.


#include "Widgets/Widget_ActivatableWidgetBase.h"
#include "Controllers/GD_FrontendPlayerController.h"

AGD_FrontendPlayerController* UWidget_ActivatableWidgetBase::GetOwningFrontendPlayerController()
{
	if (!CachedOwningFrontendPC.IsValid())
	{
		CachedOwningFrontendPC = GetOwningPlayer<AGD_FrontendPlayerController>();
	}

	return CachedOwningFrontendPC.IsValid() ? CachedOwningFrontendPC.Get() : nullptr;
}
