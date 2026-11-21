// Gondos Daniel all rights reserved.


#include "AbilitySystem/GameplayEffectCalculations/MMCs/GD_MMC_FreezeDamage.h"

#include "GD_GameplayTags.h"
#include "AbilitySystem/GD_AttributeSet.h"

UGD_MMC_FreezeDamage::UGD_MMC_FreezeDamage()
{
	HealthDef = FGameplayEffectAttributeCaptureDefinition(
		UGD_AttributeSet::GetHealthAttribute(),
		EGameplayEffectAttributeCaptureSource::Target, false);
	
	RelevantAttributesToCapture.Add(HealthDef);
}

float UGD_MMC_FreezeDamage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	FAggregatorEvaluateParameters EvalParams;
	EvalParams.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvalParams.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	float Health = 0.f;
	GetCapturedAttributeMagnitude(HealthDef, Spec, EvalParams, Health);
	
	float Damage = BaseDamage.GetValueAtLevel(Spec.GetLevel());
	//float Damage = Spec.GetSetByCallerMagnitude(GASTags::SetByCaller::FILLTAG, false, 0.f);  //TODO if I decide to drive this effect the SetByCaller way

	if (EvalParams.TargetTags && EvalParams.TargetTags->HasTag(GASTags::Status::Wet))
	{
		Damage += (Health * FreezeDamageMultiplierFromHealth);
	}
	
	return -Damage;
}
