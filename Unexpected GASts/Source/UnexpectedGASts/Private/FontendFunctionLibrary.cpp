// Gondos Daniel all rights reserved.


#include "FontendFunctionLibrary.h"
#include "FrontendSettings/FrontendDeveloperSettings.h"
#include "Widgets/Widget_PrimaryLayout.h"

TSoftClassPtr<UWidget_PrimaryLayout> UFontendFunctionLibrary::GetPrimaryLayoutWidgetClass()
{
	const UFrontendDeveloperSettings* FrontendDeveloperSettings = GetDefault<UFrontendDeveloperSettings>();
	checkf(FrontendDeveloperSettings->PrimaryLayoutWidgetClass, TEXT("Cound not find the PrimaryLayoutWidgetClass"));

	return FrontendDeveloperSettings->PrimaryLayoutWidgetClass;
}

TSoftClassPtr<UWidget_ActivatableWidgetBase> UFontendFunctionLibrary::GetFrontendSoftWidgetClassByTag(
	UPARAM(meta = (Categories = "Frontend.Widget")) FGameplayTag InWidgetTag)
{
	const UFrontendDeveloperSettings* FrontendDeveloperSettings = GetDefault<UFrontendDeveloperSettings>();
	checkf(FrontendDeveloperSettings->FrontendWidgetMap.Contains(InWidgetTag),
	       TEXT("Cound not find the corresponding widget under the tag %s"), *InWidgetTag.ToString());

	return FrontendDeveloperSettings->FrontendWidgetMap.FindRef(InWidgetTag);
}

TSoftObjectPtr<UTexture2D> UFontendFunctionLibrary::GetOptionsSoftImageByTag(FGameplayTag InImageTag)
{
	const UFrontendDeveloperSettings* FrontendDeveloperSettings = GetDefault<UFrontendDeveloperSettings>();
	checkf(FrontendDeveloperSettings->OptionsScreenSoftImageMap.Contains(InImageTag),
		   TEXT("Cound not find the corresponding image under the tag %s"), *InImageTag.ToString());

	return FrontendDeveloperSettings->OptionsScreenSoftImageMap.FindRef(InImageTag);
}

bool UFontendFunctionLibrary::FileSaveString(FString StringToSave, FString FilePath)
{
	return FFileHelper::SaveStringToFile(StringToSave, *(FPaths::ProjectContentDir() + FilePath));
}

bool UFontendFunctionLibrary::FileLoadString(FString FilePath, FString& OutString)
{
	return FFileHelper::LoadFileToString(OutString, *(FPaths::ProjectContentDir() + FilePath));
}
