// Gondos Daniel all rights reserved.


#include "Widgets/Credits/Widget_CreditsScreen.h"

#include "EnhancedActionKeyMapping.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "FrontendTypes/FrontendEnumTypes.h"
#include "Input/CommonBoundActionBar.h"
#include "Subsystems/FrontendHapticsSubsystem.h"
#include "UserSettings/EnhancedInputUserSettings.h"


void UWidget_CreditsScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CommonButton_SpeedUpCredits->OnPressed().AddUObject(this, &ThisClass::SpeedUpScrollingSpeed);
	CommonButton_SpeedUpCredits->OnReleased().AddUObject(this, &ThisClass::ResetScrollingSpeed);

	UEnhancedInputLocalPlayerSubsystem* EISubsystem = GetOwningLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(EISubsystem);
	UEnhancedInputUserSettings* EIUserSettings = EISubsystem->GetUserSettings();
	check(EIUserSettings);

	if (InputMapping)
	{
		for (FEnhancedActionKeyMapping Element : InputMapping->GetMappings())
		{
			if (Element.Action == CommonButton_SpeedUpCredits->TriggeringEnhancedInputAction)
				TriggeringSpeedUpKeys.AddUnique(Element.Key);
		}
	}
}

void UWidget_CreditsScreen::NativeOnActivated()
{
	CommonButton_SpeedUpCredits->SetVisibility(ESlateVisibility::Hidden);
	
	ResetScrollingSpeed();
	
	Super::NativeOnActivated();
}

FReply UWidget_CreditsScreen::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetCursorDelta().ComponentwiseAllGreaterThan(FDeprecateSlateVector2D(2.f, 2.f)))
		CommonButton_SpeedUpCredits->SetVisibility(ESlateVisibility::Visible);
	return Super::NativeOnMouseMove(InGeometry, InMouseEvent);
}

FReply UWidget_CreditsScreen::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	CommonButton_SpeedUpCredits->SetVisibility(ESlateVisibility::Visible);

	for (FKey Key : TriggeringSpeedUpKeys)
	{
		if (Key == InKeyEvent.GetKey())
		{
			SpeedUpScrollingSpeed();
			UFrontendHapticsSubsystem::Get(GetOwningLocalPlayer())->PlayDefaultWeakFeedbackEffect(ERumbleType::Menu);
			return FReply::Handled();
		}
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

FReply UWidget_CreditsScreen::NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	for (FKey Key : TriggeringSpeedUpKeys)
	{
		if (Key == InKeyEvent.GetKey())
		{
			ResetScrollingSpeed();
			return FReply::Handled();
		}
	}

	return Super::NativeOnKeyUp(InGeometry, InKeyEvent);
}

void UWidget_CreditsScreen::SpeedUpScrollingSpeed()
{
	CurrentScrollingSpeed = ScrollingBaseSpeed * ScrollSpeedMultiplier;
}

void UWidget_CreditsScreen::ResetScrollingSpeed()
{
	CurrentScrollingSpeed = ScrollingBaseSpeed;
}
