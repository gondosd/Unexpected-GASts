// Gondos Daniel all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "GD_MMC_FreezeDamage.generated.h"

UCLASS(Abstract)
class UNEXPECTEDGASTS_API UGD_MMC_FreezeDamage : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

	UGD_MMC_FreezeDamage();

public:
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	
	UPROPERTY(EditDefaultsOnly, Category="Damage", meta=(AllowPrivateAccess))
	FScalableFloat BaseDamage = FScalableFloat(10.f);
	
	UPROPERTY(EditDefaultsOnly, Category="Damage", meta=(AllowPrivateAccess))
	float FreezeDamageMultiplierFromHealth = 0.5f;
	
	FGameplayEffectAttributeCaptureDefinition HealthDef;
};
