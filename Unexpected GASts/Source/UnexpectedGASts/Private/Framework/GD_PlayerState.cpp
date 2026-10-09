// Copyright Daniel Göndös 2026


#include "Framework/GD_PlayerState.h"
#include "AbilitySystem/GD_AbilitySystemComponent.h"
#include "AbilitySystem/GD_AttributeSet.h"

AGD_PlayerState::AGD_PlayerState()
{
	SetNetUpdateFrequency(100.f);
	
	AbilitySystemComponent = CreateDefaultSubobject<UGD_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UGD_AttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AGD_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AGD_PlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
