// Gondos Daniel all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "FontendFunctionLibrary.generated.h"


class UAbilitySystemComponent;
class UWidget_PrimaryLayout;
class UWidget_ActivatableWidgetBase;


UCLASS()
class UNEXPECTEDGASTS_API UFontendFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

public:
	
#pragma region CommonUI

	UFUNCTION(BlueprintPure, Category = "Frontend Function Library")
	static TSoftClassPtr<UWidget_PrimaryLayout> GetPrimaryLayoutWidgetClass();
	
	UFUNCTION(BlueprintPure, Category = "Frontend Function Library")
	static TSoftClassPtr<UWidget_ActivatableWidgetBase> GetFrontendSoftWidgetClassByTag(UPARAM(meta = (Categories = "Frontend.Widget")) FGameplayTag InWidgetTag);
	
	UFUNCTION(BlueprintPure, Category = "Frontend Function Library")
	static TSoftObjectPtr<UTexture2D> GetOptionsSoftImageByTag(UPARAM(meta = (Categories = "Frontend.Image")) FGameplayTag InImageTag);
	
	UFUNCTION(BlueprintCallable, Category = "save")
	static bool FileSaveString(FString StringToSave, FString FilePath);

	UFUNCTION(BlueprintPure, Category = "save")
	static bool FileLoadString(FString FilePath, FString& OutString);
	
#pragma endregion
	
#pragma region GAS
	
	/**
	 * Gets time information about the States/Status effects. 
	 * @param ASC Ability System component to inspect
	 * @param TagToWatch The Status Tag that we want to inpect
	 * @param OutMaxDuration The max duration that the effect had when started
	 * @return Time of the effect that passed. Infinite effects has value of -1
	 */
	UFUNCTION(BlueprintCallable, Category = "GAS")
	static float GetTagTimeRemaining(UAbilitySystemComponent* ASC, FGameplayTag TagToWatch, float& OutMaxDuration);
	
#pragma endregion
};
