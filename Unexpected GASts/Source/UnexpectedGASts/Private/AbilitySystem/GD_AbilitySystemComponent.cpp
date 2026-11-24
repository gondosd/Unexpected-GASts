// Copyright Daniel Göndös 2026


#include "AbilitySystem/GD_AbilitySystemComponent.h"

//#include "AbilitySystem/Abilities/GAS_GameplayAbility.h"


void UGD_AbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);

	HandleAutoActivatedAbility(AbilitySpec);
}

void UGD_AbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	//Göndi Fix: this makes no sense here, spamming the clients, which cant activate the abilities because they are already active on the server (?)
	// FScopedAbilityListLock ActiveScopeLock(*this); // it prevents us to access an ability when it has been removed
	// for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	// {
	// 	//GiveAbilityAndActivateOnce(AbilitySpec); <- this would do the same, but once the ability is done, it will be removed
	// 	HandleAutoActivatedAbility(AbilitySpec);
	// }
}

void UGD_AbilitySystemComponent::SetAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level)
{
	if (!GetAvatarActor() || !GetAvatarActor()->HasAuthority()) return;

	if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(AbilityClass))
	{
		AbilitySpec->Level = Level;
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

void UGD_AbilitySystemComponent::AddToAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 LevelToAdd)
{
	if (!GetAvatarActor() || !GetAvatarActor()->HasAuthority()) return;

	if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(AbilityClass))
	{
		AbilitySpec->Level += LevelToAdd;
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

float UGD_AbilitySystemComponent::GetTagTimeRemaining(FGameplayTag TagToWatch, float& OutMaxDuration) const
{
	OutMaxDuration = 0.f;
	
	FGameplayEffectQuery Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(FGameplayTagContainer(TagToWatch));

	TArray<TPair<float, float>> TimeAndDuration = GetActiveEffectsTimeRemainingAndDuration(Query);
	if (TimeAndDuration.Num() == 0) return 0.f;

	// If several effects grant the same tag the longest one counts
	float BestRemaining = 0.f;
	for (const TPair<float, float>& Pair : TimeAndDuration)
	{
		if (Pair.Key > BestRemaining)
		{
			BestRemaining = Pair.Key;
			OutMaxDuration = Pair.Value;
		}
	}
	return BestRemaining;
}

void UGD_AbilitySystemComponent::HandleAutoActivatedAbility(const FGameplayAbilitySpec& AbilitySpec)
{
	//TODO: i want to reconsider this direction and maybe remove activate on given tag alltogether
	
	// if (!AbilitySpec.Ability) return;
	//
	// for (const FGameplayTag Tag : AbilitySpec.Ability->GetAssetTags())
	// {
	// 	if (Tag.MatchesTagExact(GASTags::GASAbilities::ActivateOnGiven))
	// 	{
	// 		TryActivateAbility(AbilitySpec.Handle);
	// 		return;
	// 	}
	// }
}
