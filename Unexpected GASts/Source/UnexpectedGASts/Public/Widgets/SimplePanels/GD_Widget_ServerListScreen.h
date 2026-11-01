// Gondos Daniel all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_ActivatableWidgetBase.h"
#include "GD_Widget_ServerListScreen.generated.h"

class UDynamicEntryBox;
class UCommonLazyImage;
struct FBlueprintSessionResult;
class UInputAction;

UCLASS()
class UNEXPECTEDGASTS_API UGD_Widget_ServerListScreen : public UWidget_ActivatableWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeOnActivated() override;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta = (DisplayName = "Start Search"))
	void BP_StartSearch();
	
private:
	virtual void NativeOnInitialized() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "ServerList", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	UInputAction* RefreshAction;
	
	//FUIActionBindingHandle RefreshActionHandle;
	
};
