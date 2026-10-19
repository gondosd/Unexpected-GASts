// Copyright Daniel Göndös 2026


#include "Controllers/GD_GameplayPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GD_GameplayTags.h"
#include "Characters/GD_BaseCharacter.h"
#include "GameFramework/Character.h"

class UEnhancedInputLocalPlayerSubsystem;

void AGD_GameplayPlayerController::SetupInputComponent()
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

void AGD_GameplayPlayerController::Jump()
{
	if (!IsValid(GetCharacter())) return;
	if (!IsAlive()) return;
	
	GetCharacter()->Jump();
}

void AGD_GameplayPlayerController::StopJumping()
{
	if (!IsValid(GetCharacter())) return;
	if (!IsAlive()) return;
	
	GetCharacter()->StopJumping();
}

void AGD_GameplayPlayerController::Move(const FInputActionValue& Value)
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

void AGD_GameplayPlayerController::Look(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn())) return;
	if (!IsAlive()) return;
	
	const FVector& LookAxisVector = Value.Get<FVector>();
	
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void AGD_GameplayPlayerController::Primary()
{
	//ActivateAbility(GASTags::GASAbilities::Primary);
}

void AGD_GameplayPlayerController::Secondary()
{
	//ActivateAbility(GASTags::GASAbilities::Secondary);
}

void AGD_GameplayPlayerController::Tertiary()
{
	//ActivateAbility(GASTags::GASAbilities::Tertiary);
}

void AGD_GameplayPlayerController::ActivateAbility(const FGameplayTag& AbilityTag) const
{
	if (!IsAlive()) return;
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	if (!ASC) return;
	
	ASC->TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());
}

bool AGD_GameplayPlayerController::IsAlive() const
{
	 const AGD_BaseCharacter* BaseCharacter = Cast<AGD_BaseCharacter>(GetPawn());
	if (!BaseCharacter) return false;
	
	return BaseCharacter->IsAlive();
}
