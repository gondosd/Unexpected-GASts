// Copyright Daniel Göndös 2026

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "GD_PlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class UNEXPECTEDGASTS_API AGD_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGD_PlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;

private:
	UPROPERTY(VisibleAnywhere, Category = "GAS|Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
