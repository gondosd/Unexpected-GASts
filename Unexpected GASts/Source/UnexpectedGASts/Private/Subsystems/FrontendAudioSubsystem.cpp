// Gondos Daniel all rights reserved.


#include "Subsystems/FrontendAudioSubsystem.h"

#include "FrontendSettings/FrontendDeveloperSettings.h"
#include "FrontendSettings/FrontendGameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"

//static variable initializations
const UFrontendDeveloperSettings* UFrontendAudioSubsystem::CachedFrontendDeveloperSettings = nullptr;

UFrontendAudioSubsystem* UFrontendAudioSubsystem::Get(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);
		return UGameInstance::GetSubsystem<UFrontendAudioSubsystem>(World->GetGameInstance());
	}

	return nullptr;
}

void UFrontendAudioSubsystem::InitializeAudioSettings()
{
	SetMasterVolume(UFrontendGameUserSettings::Get()->GetOverallVolume());
	SetMusicVolume(UFrontendGameUserSettings::Get()->GetMusicVolume());
	SetSFXVolume(UFrontendGameUserSettings::Get()->GetSFXVolume());
}

void UFrontendAudioSubsystem::SetMasterVolume(float InMasterVolume)
{
	if (!CachedFrontendDeveloperSettings)
		CachedFrontendDeveloperSettings = GetDefault<UFrontendDeveloperSettings>();
	
	if (UObject* LoadedSoundClass = CachedFrontendDeveloperSettings->MasterSoundClass.TryLoad())
		SetVolume(InMasterVolume, LoadedSoundClass);
}

void UFrontendAudioSubsystem::SetMusicVolume(float InMusicVolume)
{
	if (!CachedFrontendDeveloperSettings)
		CachedFrontendDeveloperSettings = GetDefault<UFrontendDeveloperSettings>();
	
	if (UObject* LoadedSoundClass = CachedFrontendDeveloperSettings->MusicSoundClass.TryLoad())
		SetVolume(InMusicVolume, LoadedSoundClass);
}

void UFrontendAudioSubsystem::SetSFXVolume(float InSFXVolume)
{
	if (!CachedFrontendDeveloperSettings)
		CachedFrontendDeveloperSettings = GetDefault<UFrontendDeveloperSettings>();
	
	if (UObject* LoadedSoundClass = CachedFrontendDeveloperSettings->SoundFXSoundClass.TryLoad())
		SetVolume(InSFXVolume, LoadedSoundClass);
}

void UFrontendAudioSubsystem::SetVolume(float InVolume, UObject* LoadedSoundClass)
{
	if (!CachedFrontendDeveloperSettings)
		CachedFrontendDeveloperSettings = GetDefault<UFrontendDeveloperSettings>();
	check(CachedFrontendDeveloperSettings);
	
	UWorld* World = GEngine ? GEngine->GetCurrentPlayWorld() : nullptr;
	if (!World) return;
	
	USoundClass* MusicSoundClass = Cast<USoundClass>(LoadedSoundClass);
	
	USoundMix* DefaultSoundMix = nullptr;
	if (UObject* LoadedObject = CachedFrontendDeveloperSettings->DefaultSoundMix.TryLoad())
		DefaultSoundMix = Cast<USoundMix>(LoadedObject);
	
	
	if (!DefaultSoundMix || !MusicSoundClass) return;
	
	UGameplayStatics::SetSoundMixClassOverride(
		World,
		DefaultSoundMix,
		MusicSoundClass,
		InVolume,
		1.f,
		0.f
	);
	
	UGameplayStatics::PushSoundMixModifier(World, DefaultSoundMix);
}

void UFrontendAudioSubsystem::Deinitialize()
{
	Super::Deinitialize();
	
	//Clear out unused raw pointers
	CachedFrontendDeveloperSettings = nullptr;
}
