// Gondos Daniel all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FrontendAudioSubsystem.generated.h"

class UFrontendDeveloperSettings;
/**
 * 
 */
UCLASS()
class FRONTENDUI_API UFrontendAudioSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	static UFrontendAudioSubsystem* Get(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable)
	void InitializeAudioSettings();
	virtual void Deinitialize() override;
	
	static void SetMasterVolume(float InMasterVolume);
	static void SetMusicVolume(float InMusicVolume);
	static void SetSFXVolume(float InSFXVolume);
	
	static void SetVolume(float InVolume, UObject* LoadedSoundClass);
	
private:
	static UWorld* CachedWorld;
	
	static const UFrontendDeveloperSettings* CachedFrontendDeveloperSettings;

	
};
