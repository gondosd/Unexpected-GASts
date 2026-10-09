// Copyright Daniel Göndös 2026


#include "Framework/GD_PlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GD_GameplayTags.h"
#include "Characters/GD_BaseCharacter.h"
#include "GameFramework/Character.h"

class UEnhancedInputLocalPlayerSubsystem;

void AGD_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(InputSubsystem)) return;

	for (TObjectPtr<UInputMappingContext> Context : InputMappingContexts)
	{
		InputSubsystem->AddMappingContext(Context, 0);
	}
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)) return;
	
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	
	EnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Triggered, this, &ThisClass::Primary);
	EnhancedInputComponent->BindAction(SecondaryAction, ETriggerEvent::Triggered, this, &ThisClass::Secondary);
	EnhancedInputComponent->BindAction(TertiaryAction, ETriggerEvent::Triggered, this, &ThisClass::Tertiary);
}

void AGD_PlayerController::Jump()
{
	if (!IsValid(GetCharacter())) return;
	if (!IsAlive()) return;
	
	GetCharacter()->Jump();
}

void AGD_PlayerController::StopJumping()
{
	if (!IsValid(GetCharacter())) return;
	if (!IsAlive()) return;
	
	GetCharacter()->StopJumping();
}

void AGD_PlayerController::Move(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn())) return;
	if (!IsAlive()) return;
	
	const FVector& MovementVector = Value.Get<FVector>();
	
	//Find which was is forward
	const FRotator YawRotation (0.f, GetControlRotation().Yaw, 0.f); 
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetPawn()->AddMovementInput(RightVector, MovementVector.X);

}

void AGD_PlayerController::Look(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn())) return;
	if (!IsAlive()) return;
	
	const FVector& LookAxisVector = Value.Get<FVector>();
	
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void AGD_PlayerController::Primary()
{
	//ActivateAbility(GASTags::GASAbilities::Primary);
}

void AGD_PlayerController::Secondary()
{
	//ActivateAbility(GASTags::GASAbilities::Secondary);
}

void AGD_PlayerController::Tertiary()
{
	//ActivateAbility(GASTags::GASAbilities::Tertiary);
}

void AGD_PlayerController::ActivateAbility(const FGameplayTag& AbilityTag) const
{
	if (!IsAlive()) return;
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	if (!ASC) return;
	
	ASC->TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());
}

bool AGD_PlayerController::IsAlive() const
{
	 const AGD_BaseCharacter* BaseCharacter = Cast<AGD_BaseCharacter>(GetPawn());
	if (!BaseCharacter) return false;
	
	return BaseCharacter->IsAlive();
}
