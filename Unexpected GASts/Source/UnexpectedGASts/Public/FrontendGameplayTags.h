// Gondos Daniel all rights reserved.

#pragma once

#include "NativeGameplayTags.h"

namespace FrontendGameplayTags
{
	//Frontend widget stack
	UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_Modal);
	UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_GameMenu);
	UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_GameHud);
	UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_Frontend);

	//Frontend widgets
	UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_PressAnyKeyScreen);
	UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_MainMenuScreen);
	UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_OptionsScreen);
	
	UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_ConfirmScreen);
	UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_KeyRemapScreen);

	//Frontend Options Image
	UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Image_TestImage);
	
	
}