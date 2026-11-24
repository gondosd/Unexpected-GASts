// Gondos Daniel all rights reserved.


#include "Widgets/Components/GD_BuffWidget.h"

#include "AbilitySystemComponent.h"
#include "FontendFunctionLibrary.h"

void UGD_BuffWidget::NativeConstruct()
{
	checkf(TagToWatch.IsValid(), TEXT("TagToWatch is not set"));	
	Super::NativeConstruct();
}

void UGD_BuffWidget::NativeDestruct()
{
	StopTimer();
	Super::NativeDestruct();
}

void UGD_BuffWidget::InitializeWidget(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	if (!ASC) return;
	
	Cached_ASC = ASC;
	TagStateChanged(); //Init

	BindTagChanges();
}

void UGD_BuffWidget::BindTagChanges()
{
	Cached_ASC.Get()->RegisterGameplayTagEvent(TagToWatch).AddLambda(
		[this](const FGameplayTag Tag, int32 NewCount)
		{
			if (NewCount > 0)
			{
				SetVisibility(ESlateVisibility::HitTestInvisible);
				StartTimer();
			}
			else
			{
				SetVisibility(ESlateVisibility::Collapsed);
				StopTimer();
			}
		});
}


void UGD_BuffWidget::StartTimer()
{
	if (const UWorld* World = GetWorld())
		World->GetTimerManager().SetTimer(UpdateHandle, this, &UGD_BuffWidget::TagStateChanged, 0.05f, true);
}

void UGD_BuffWidget::StopTimer()
{
	if (const UWorld* World = GetWorld())
		World->GetTimerManager().ClearTimer(UpdateHandle);
}

void UGD_BuffWidget::TagStateChanged()
{
	float MaxTime;
	const float CurrentTime = UFontendFunctionLibrary::GetTagTimeRemaining(Cached_ASC.Get(), TagToWatch, MaxTime);

	BP_TagTimeChange(CurrentTime, MaxTime);
}
