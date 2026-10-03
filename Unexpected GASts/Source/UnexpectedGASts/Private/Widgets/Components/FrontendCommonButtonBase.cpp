// Gondos Daniel all rights reserved.


#include "Widgets/Components/FrontendCommonButtonBase.h"

#include "CommonLazyImage.h"
#include "CommonTextBlock.h"
#include "Subsystems/FrontendHapticsSubsystem.h"
#include "Subsystems/FrontendUISubsystem.h"

void UFrontendCommonButtonBase::SetButtonText(FText InText)
{
	if (CommonTextBlock_ButtonText && !InText.IsEmpty())
	{
		CommonTextBlock_ButtonText->SetText(bUseUpperCaseForButtonText ? InText.ToUpper() : InText);
	}
}

FText UFrontendCommonButtonBase::GetButtonDisplayText() const
{
	if (CommonTextBlock_ButtonText)
	{
		return CommonTextBlock_ButtonText->GetText();
	}
	return FText::GetEmpty();
}

void UFrontendCommonButtonBase::SetButtonDisplayImage(const FSlateBrush& InBrush)
{
	if (CommonLazyImage_ButtonImage)
	{
		CommonLazyImage_ButtonImage->SetBrush(InBrush);
	}
}

void UFrontendCommonButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetButtonText(ButtonDisplayText);
}

void UFrontendCommonButtonBase::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();

	if (CommonTextBlock_ButtonText && GetCurrentTextStyleClass())
	{
		CommonTextBlock_ButtonText->SetStyle(GetCurrentTextStyleClass());
	}
}

void UFrontendCommonButtonBase::NativeOnHovered()
{
	Super::NativeOnHovered();
	if (!ButtonDescriptionText.IsEmpty())
	{
		UFrontendUISubsystem::Get(this)->OnButtonDescriptionTextUpdatedDelegate.Broadcast(this, ButtonDescriptionText);
	}
	
	UFrontendHapticsSubsystem::Get(GetOwningLocalPlayer())->PlayDefaultWeakFeedbackEffect(ERumbleType::Menu);
}

void UFrontendCommonButtonBase::NativeOnClicked()
{
	Super::NativeOnClicked();
	UFrontendHapticsSubsystem::Get(GetOwningLocalPlayer())->PlayDefaultStrongFeedbackEffect(ERumbleType::Menu);
	
}

void UFrontendCommonButtonBase::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();

	UFrontendUISubsystem::Get(this)->OnButtonDescriptionTextUpdatedDelegate.Broadcast(this, FText::GetEmpty());
}
