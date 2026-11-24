// Gondos Daniel all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GD_StatusWidget.h"
#include "GD_BuffWidget.generated.h"


class UAttributeSet;
class UAbilitySystemComponent;
class AGD_BaseCharacter;

UCLASS()
class UNEXPECTEDGASTS_API UGD_BuffWidget : public UGD_StatusWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	virtual void InitializeWidget(UAbilitySystemComponent* ASC, UAttributeSet* AS) override;
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Tag Change"))
	void BP_TagTimeChange(float CurrentTime, float MaxTime);
	
private:
	void BindTagChanges();
	void TagStateChanged();
	
	void StartTimer();
	void StopTimer();
	
	TWeakObjectPtr<UAbilitySystemComponent> Cached_ASC;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Tags", meta =(AllowPrivateAccess = true))
	FGameplayTag TagToWatch;
	
	FTimerHandle UpdateHandle;
};
