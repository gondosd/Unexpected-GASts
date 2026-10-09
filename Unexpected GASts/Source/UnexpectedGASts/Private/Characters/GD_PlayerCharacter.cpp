// Copyright Daniel Göndös 2026


#include "Characters/GD_PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/GD_AttributeSet.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Framework/GD_PlayerState.h"


AGD_PlayerCharacter::AGD_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 200.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	Tags.Add(GASActorTags::Player);
}

UAbilitySystemComponent* AGD_PlayerCharacter::GetAbilitySystemComponent() const
{
	const AGD_PlayerState* GAS_PlayerState = Cast<AGD_PlayerState>(GetPlayerState());
	if (!IsValid(GAS_PlayerState)) return nullptr;

	return GAS_PlayerState->GetAbilitySystemComponent();
}

UAttributeSet* AGD_PlayerCharacter::GetAttributeSet() const
{
	if (AGD_PlayerState* Playerstate = Cast<AGD_PlayerState>(GetPlayerState()))
		return Playerstate->GetAttributeSet();
	
	return nullptr;
}

void AGD_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!GetAbilitySystemComponent() || !HasAuthority()) return;

	//this runs on server
	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	GiveStartupAbilities();
	InitializeAttributes(InitializeAttributeEffect);
	
	UGD_AttributeSet* AttributeSet = Cast<UGD_AttributeSet>(GetAttributeSet());
	if (!AttributeSet) return;
	
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
}

void AGD_PlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (!GetAbilitySystemComponent()) return;

	//this runs on clients
	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	
	UGD_AttributeSet* AttributeSet = Cast<UGD_AttributeSet>(GetAttributeSet());
	if (!AttributeSet) return;
	
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
}
