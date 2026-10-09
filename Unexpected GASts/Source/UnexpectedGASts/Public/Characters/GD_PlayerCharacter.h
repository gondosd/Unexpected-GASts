// Copyright Daniel Göndös 2026

#pragma once

#include "CoreMinimal.h"
#include "GD_BaseCharacter.h"
#include "GD_PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS(Abstract)
class UNEXPECTEDGASTS_API AGD_PlayerCharacter : public AGD_BaseCharacter
{
	GENERATED_BODY()

public:
	AGD_PlayerCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
};
