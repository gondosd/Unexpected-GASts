// Gondos Daniel all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Widgets/Widget_ActivatableWidgetBase.h"
#include "Widget_CreditsScreen.generated.h"


class UFrontendCommonBoundActionBar;
class UCommonButtonBase;
/**
 * 
 */
UCLASS()
class FRONTENDUI_API UWidget_CreditsScreen : public UWidget_ActivatableWidgetBase
{
	GENERATED_BODY()
	
	
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnActivated() override;

	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	
	UFUNCTION(BlueprintPure, meta = (HideSelfPin = "true"))
	FORCEINLINE float GetScrollingSpeed() const {return CurrentScrollingSpeed;};
	
private:
#pragma region Bindigns

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonButtonBase> CommonButton_SpeedUpCredits;
	
#pragma endregion
	
	void SpeedUpScrollingSpeed();
	void ResetScrollingSpeed();
	
	
	UPROPERTY(EditDefaultsOnly, Category = "Scrolling Speed")
	float ScrollingBaseSpeed = 1.f;
	UPROPERTY(EditDefaultsOnly, Category = "Scrolling Speed")
	float ScrollSpeedMultiplier = 10.f;
	
	float CurrentScrollingSpeed = ScrollingBaseSpeed;
	
	TArray<FKey> TriggeringSpeedUpKeys;
};
