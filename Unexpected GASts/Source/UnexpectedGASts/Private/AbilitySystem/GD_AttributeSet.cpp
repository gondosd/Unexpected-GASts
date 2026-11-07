// Copyright Daniel Göndös 2026


#include "AbilitySystem/GD_AttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GD_GameplayTags.h"
#include "Net/UnrealNetwork.h"

void UGD_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, bAttributesInitialized)

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHealth, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Mana, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxMana, COND_None, REPNOTIFY_Always)
}

void UGD_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	//Clamping... it feels weird to do it here, and like this. TODO: fix this somewhere else because its not working from the tutorial!
	// if (Data.EvaluatedData.Attribute == GetHealthAttribute() && bAttributesInitialized)
	// 	SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	//
	// if (Data.EvaluatedData.Attribute == GetManaAttribute() && bAttributesInitialized)
	// 	SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));

	if (Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth() <= 0.f)
	{
		UAbilitySystemComponent* ASC = &Data.Target;
		if (!ASC->HasMatchingGameplayTag(GASTags::States::Dead))
		{
			ASC->AddLooseGameplayTag(GASTags::States::Dead, 1, EGameplayTagReplicationState::TagOnly);

			FGameplayEventData Payload;
			Payload.Instigator = Data.Target.GetAvatarActor();
			//TODO: implement this KillScored part
			//UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Data.EffectSpec.GetEffectContext().GetInstigator(), GASTags::Events::KillScored, Payload);
		}
	}

	if (!bAttributesInitialized)
	{
		bAttributesInitialized = true;
		OnAttributesInitialized.Broadcast();
	}
}

void UGD_AttributeSet::OnRep_AttributesInitialized()
{
	if (bAttributesInitialized)
	{
		OnAttributesInitialized.Broadcast();
	}
}

void UGD_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Health, OldValue);
}

void UGD_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHealth, OldValue);
}

void UGD_AttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Mana, OldValue);
}

void UGD_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxMana, OldValue);
}
