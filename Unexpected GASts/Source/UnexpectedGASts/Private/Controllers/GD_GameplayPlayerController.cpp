// Copyright Daniel Göndös 2026


#include "Controllers/GD_GameplayPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FontendFunctionLibrary.h"
#include "GD_GameplayTags.h"
#include "Characters/GD_BaseCharacter.h"
#include "GameFramework/Character.h"
#include "Subsystems/FrontendAudioSubsystem.h"
#include "Subsystems/FrontendUISubsystem.h"
#include "Widgets/Widget_ActivatableWidgetBase.h"

class UEnhancedInputLocalPlayerSubsystem;

void AGD_GameplayPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)) return;
	
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	EnhancedInputComponent->BindAction(OpenMenuAction, ETriggerEvent::Triggered, this, &ThisClass::ToggleMenu);
	
	EnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Triggered, this, &ThisClass::Primary);
	EnhancedInputComponent->BindAction(SecondaryAction, ETriggerEvent::Triggered, this, &ThisClass::Secondary);
	EnhancedInputComponent->BindAction(TertiaryAction, ETriggerEvent::Triggered, this, &ThisClass::Tertiary);
	EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &ThisClass::Dash);
	EnhancedInputComponent->BindAction(EmoteAction, ETriggerEvent::Triggered, this, &ThisClass::Emote);
	EnhancedInputComponent->BindAction(ResurrectAction, ETriggerEvent::Triggered, this, &ThisClass::Resurrect);
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

void AGD_GameplayPlayerController::ToggleMenu()
{
	if (UFrontendUISubsystem* FrontendUISubsystem = UFrontendUISubsystem::Get(this))
	{
		if (FrontendUISubsystem->CheckWidgetStackIfEmptyByTag(FrontendGameplayTags::Stacks::Frontend_WidgetStack_GameMenu))
		{
			FrontendUISubsystem->ClearEntireWidgetStackByTag(FrontendGameplayTags::Stacks::Frontend_WidgetStack_GameMenu);
			//SetPause(false); //TODO think if multiplayer should be paused here
			//UFrontendAudioSubsystem::Get(this)->PauseMusic(false);
		}
		else
		{
			TSoftClassPtr<UWidget_ActivatableWidgetBase> PauseMenuWidget = UFontendFunctionLibrary::GetFrontendSoftWidgetClassByTag(
				FrontendGameplayTags::Widgets::Game_Widget_MenuScreen);
			FrontendUISubsystem->PushSoftWidgetToStackAsync(FrontendGameplayTags::Stacks::Frontend_WidgetStack_GameMenu,
															PauseMenuWidget,
															[this](EAsyncPushWidgetState AsyncPushWidgetState,
																   UWidget_ActivatableWidgetBase* Widget_ActivatableWidgetBase)
															{
																//TODO think if multiplayer should be paused here
																
																// Widget_ActivatableWidgetBase->OnWidgetClosed.AddUObject(
																// 	this, &AGD_GameplayPlayerController::MenuPanelClosed);
															}
			);
			//SetPause(true); //TODO think if multiplayer should be paused here
			//UFrontendAudioSubsystem::Get(this)->PauseMusic(true);
		}
	}
}

void AGD_GameplayPlayerController::Primary()
{
	ActivateAbility(GASTags::Abilities::PrimaryAttack);
}

void AGD_GameplayPlayerController::Secondary()
{
	ActivateAbility(GASTags::Abilities::SecondaryAttack);
}

void AGD_GameplayPlayerController::Tertiary()
{
	ActivateAbility(GASTags::Abilities::TertiaryAttack);
}

void AGD_GameplayPlayerController::Emote()
{
	ActivateAbility(GASTags::Abilities::Emote);
}

void AGD_GameplayPlayerController::Resurrect()
{
	ActivateAbility(GASTags::Abilities::Resurrect);
}

void AGD_GameplayPlayerController::Dash()
{
	ActivateAbility(GASTags::Abilities::Dash);
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
