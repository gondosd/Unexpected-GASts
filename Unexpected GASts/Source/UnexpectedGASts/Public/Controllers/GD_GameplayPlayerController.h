// Copyright Daniel Göndös 2026

#pragma once

#include "CoreMinimal.h"
#include "GD_PlayerControllerBase.h"
#include "GD_GameplayPlayerController.generated.h"


struct FGameplayTag;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS(Abstract)
class UNEXPECTEDGASTS_API AGD_GameplayPlayerController : public AGD_PlayerControllerBase
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "GD|Input|Movement")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "GD|Input|Movement")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "GD|Input|Movement")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "GD|Input|Abilities")
	TObjectPtr<UInputAction> PrimaryAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "GD|Input|Abilities")
	TObjectPtr<UInputAction> SecondaryAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "GD|Input|Abilities")
	TObjectPtr<UInputAction> TertiaryAction;
	
	void Jump();
	void StopJumping();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Primary();
	void Secondary();
	void Tertiary();
	void ActivateAbility(const FGameplayTag& AbilityTag) const;
	
	bool IsAlive()const;
	
};
