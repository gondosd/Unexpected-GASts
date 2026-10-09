// Copyright Daniel Göndös 2026


#include "Characters/GD_BaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

namespace GASActorTags
{
	const FName Player = FName("Player");
}

AGD_BaseCharacter::AGD_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	//Tick and refresh bone transforms whether rendered or not - for bone uptades on a dedicated server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

void AGD_BaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, bAlive);
}

UAbilitySystemComponent* AGD_BaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

void AGD_BaseCharacter::GiveStartupAbilities()
{
	if (!GetAbilitySystemComponent()) return;
	
	for (const TSubclassOf<UGameplayAbility>& Ability : Abilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
		GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
	}
}

void AGD_BaseCharacter::InitializeAttributes(TSubclassOf<UGameplayEffect> EffectsToInitializeFrom)
{
	if (!GetAbilitySystemComponent()) return;
	checkf(EffectsToInitializeFrom, TEXT("EffectsToInitializeFrom not set"));

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(EffectsToInitializeFrom, 1.f, ContextHandle);
	
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void AGD_BaseCharacter::OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData)
{
	if (AttributeChangeData.NewValue < 0.f)
		HandleDeath();
}

void AGD_BaseCharacter::HandleDeath()
{
	bAlive = false;
}

void AGD_BaseCharacter::ResetAttributes()
{
	if (!HasAuthority()) return;
	
	InitializeAttributes(ResetAttributeEffect);
	
}

void AGD_BaseCharacter::HandleRespawn()
{
	bAlive = true;
}
