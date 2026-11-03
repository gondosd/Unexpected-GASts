// Gondos Daniel all rights reserved.

#pragma once

#include "NativeGameplayTags.h"

namespace FrontendGameplayTags
{
	namespace Stacks
	{
		//Frontend widget stack
		UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_Modal);
		UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_GameMenu);
		UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_GameHud);
		UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_Frontend);
	}

	namespace Widgets
	{
		//Frontend widgets
		UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_PressAnyKeyScreen);
		UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_MainMenuScreen);
		UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_OptionsScreen);

		UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_ConfirmScreen);
		UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_KeyRemapScreen);
		
		//In-game Widgets
		UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Game_Widget_MenuScreen);
	}

	namespace Images
	{
		//Frontend Options Image
		UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Image_TestImage);
	}
}

namespace GASTags
{
	namespace Abilities
	{
		UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(PrimaryAttack);
		UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SecondaryAttack);
		UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TertiaryAttack);
		UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(BaseAttack);
		UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Dash);
		UNEXPECTEDGASTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Emote);
	}

	namespace SetByCaller
	{
		//Projectile
	}

	namespace Event
	{
		//Combat
			//DamageTaken
			//Healed
			//Kill
		//System
			//QuestCompleted
	}

	namespace State
	{
		//Dead
		//Stunned
		//Invulnerable
		//Airborne
	}

	namespace Cooldown
	{
	}
}
