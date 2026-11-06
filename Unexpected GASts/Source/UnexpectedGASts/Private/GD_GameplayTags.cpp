// Gondos Daniel all rights reserved.


#include "GD_GameplayTags.h"


namespace FrontendGameplayTags
{
	namespace Stacks
	{
		//Frontend widget stack
		UE_DEFINE_GAMEPLAY_TAG(Frontend_WidgetStack_Modal, "Frontend.WidgetStack.Modal");
		UE_DEFINE_GAMEPLAY_TAG(Frontend_WidgetStack_GameMenu, "Frontend.WidgetStack.GameMenu");
		UE_DEFINE_GAMEPLAY_TAG(Frontend_WidgetStack_GameHud, "Frontend.WidgetStack.GameHud");
		UE_DEFINE_GAMEPLAY_TAG(Frontend_WidgetStack_Frontend, "Frontend.WidgetStack.Frontend");
	}

	namespace Widgets
	{
		//Frontend widgets
		UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_PressAnyKeyScreen, "Frontend.Widget.PressAnyKeyScreen");
		UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_MainMenuScreen, "Frontend.Widget.MainMenuScreen");
		UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_OptionsScreen, "Frontend.Widget.OptionsScreen");

		UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_ConfirmScreen, "Frontend.Widget.ConfirmScreen");
		UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_KeyRemapScreen, "Frontend.Widget.KeyRemapScreen");

		//In-game Widgets
		UE_DEFINE_GAMEPLAY_TAG(Game_Widget_MenuScreen, "Frontend.Widget.GameMenuScreen");
	}

	namespace Images
	{
		//Frontend Options Image
		UE_DEFINE_GAMEPLAY_TAG(Frontend_Image_TestImage, "Frontend.Image.TestImage");
	}
}

namespace GASTags
{
	namespace Abilities
	{
		UE_DEFINE_GAMEPLAY_TAG(PrimaryAttack, "GAS.Abilities.PrimaryAttack");
		UE_DEFINE_GAMEPLAY_TAG(SecondaryAttack, "GAS.Abilities.SecondaryAttack");
		UE_DEFINE_GAMEPLAY_TAG(TertiaryAttack, "GAS.Abilities.TertiaryAttack");
		UE_DEFINE_GAMEPLAY_TAG(BaseAttack, "GAS.Abilities.BaseAttack");
		UE_DEFINE_GAMEPLAY_TAG(Dash, "GAS.Abilities.Dash");
		UE_DEFINE_GAMEPLAY_TAG(Emote, "GAS.Abilities.Emote");
	}

	namespace SetByCaller
	{
		//Projectile
	}

	namespace Events
	{
		namespace Damage
		{
			UE_DEFINE_GAMEPLAY_TAG(AttackNotify, "GAS.Events.Attacks.AttackNotify");	
		}

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
