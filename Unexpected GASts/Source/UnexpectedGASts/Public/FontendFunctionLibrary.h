// Gondos Daniel all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "FontendFunctionLibrary.generated.h"


class UWidget_ActivatableWidgetBase;


UCLASS()
class UNEXPECTEDGASTS_API UFontendFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

public:

	UFUNCTION(BlueprintPure, Category = "Frontend Function Library")
	static TSoftClassPtr<UWidget_ActivatableWidgetBase> GetFrontendSoftWidgetClassByTag(UPARAM(meta = (Categories = "Frontend.Widget")) FGameplayTag InWidgetTag);
	
	UFUNCTION(BlueprintPure, Category = "Frontend Function Library")
	static TSoftObjectPtr<UTexture2D> GetOptionsSoftImageByTag(UPARAM(meta = (Categories = "Frontend.Image")) FGameplayTag InImageTag);
	
	UFUNCTION(BlueprintCallable, Category = "save")
	static bool FileSaveString(FString StringToSave, FString FilePath);

	UFUNCTION(BlueprintPure, Category = "save")
	static bool FileLoadString(FString FilePath, FString& OutString);
};
