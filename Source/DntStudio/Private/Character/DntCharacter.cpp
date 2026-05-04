// DntStudio


#include "Character/DntCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/DntAbilitySystemComponent.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/DntPlayerController.h"
#include "Player/DntPlayerState.h"
#include "NiagaraComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UI/HUD/DntHUD.h"

ADntCharacter::ADntCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>("TopDownCameraComponent");
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;
	
	LevelUpNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("LevelUpNiagaraComponent");
	LevelUpNiagaraComponent->SetupAttachment(GetRootComponent());
	LevelUpNiagaraComponent->bAutoActivate = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	CharacterClass = ECharacterClass::Elementalist;
}

void ADntCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
//init ability actor info for the server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void ADntCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Init ability actor info for the client
    InitAbilityActorInfo();
}

void ADntCharacter::AddToXP_Implementation(int32 InXP)
{
	ADntPlayerState* DntPlayerState = GetPlayerState<ADntPlayerState>();
	check(DntPlayerState);
	DntPlayerState->AddToXP(InXP);
}

void ADntCharacter::LevelUp_Implementation()
{
	MulticastLevelUpParticles();
}

void ADntCharacter::MulticastLevelUpParticles_Implementation() const
{
	if (IsValid(LevelUpNiagaraComponent))
	{
		const FVector CameraLocation = TopDownCameraComponent->GetComponentLocation();
		const FVector NiagaraSystemLocation = LevelUpNiagaraComponent->GetComponentLocation();
		const FRotator ToCameraRotation = (CameraLocation - NiagaraSystemLocation).Rotation();
		LevelUpNiagaraComponent->SetWorldRotation(ToCameraRotation);
		LevelUpNiagaraComponent->Activate(true);
	}
}

int32 ADntCharacter::GetXP_Implementation() const
{
	const ADntPlayerState* DntPlayerState = GetPlayerState<ADntPlayerState>();
	check(DntPlayerState);
	return DntPlayerState->GetXP();
}

int32 ADntCharacter::FindLevelForXP_Implementation(int32 InXP) const
{
	const ADntPlayerState* DntPlayerState = GetPlayerState<ADntPlayerState>();
	check(DntPlayerState);
	return DntPlayerState->LevelUpInfo->FindLevelForXP(InXP);
}

int32 ADntCharacter::GetAttributePointsReward_Implementation(int32 Level) const
{
	const ADntPlayerState* DntPlayerState = GetPlayerState<ADntPlayerState>();
	check(DntPlayerState);
	return DntPlayerState->LevelUpInfo->LevelUpInformation[Level].AttributePointAward;
}

int32 ADntCharacter::GetSpellPointsReward_Implementation(int32 Level) const
{
	const ADntPlayerState* DntPlayerState = GetPlayerState<ADntPlayerState>();
	check(DntPlayerState);
	return DntPlayerState->LevelUpInfo->LevelUpInformation[Level].SpellPointAward;
}

void ADntCharacter::AddToPlayerLevel_Implementation(int32 InPlayerLevel)
{
	ADntPlayerState* DntPlayerState = GetPlayerState<ADntPlayerState>();
	check(DntPlayerState);
	DntPlayerState->AddToLevel(InPlayerLevel);
	
	if (UDntAbilitySystemComponent* DntASC = Cast<UDntAbilitySystemComponent>(GetAbilitySystemComponent()))
	{
		DntASC->UpdateAbilityStatuses(DntPlayerState->GetPlayerLevel());
	}
}

void ADntCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
{
	ADntPlayerState* DntPlayerState = GetPlayerState<ADntPlayerState>();
	check(DntPlayerState);
	DntPlayerState->AddToAttributePoints(InAttributePoints);
}

void ADntCharacter::AddToSpellPoints_Implementation(int32 InSpellPoints)
{
	ADntPlayerState* DntPlayerState = GetPlayerState<ADntPlayerState>();
	check(DntPlayerState);
	DntPlayerState->AddToSpellPoints(InSpellPoints);
}

int32 ADntCharacter::GetAttributePoints_Implementation() const
{
	ADntPlayerState* DntPlayerState = GetPlayerState<ADntPlayerState>();
	check(DntPlayerState);
	return DntPlayerState->GetAttributePoints();
}

int32 ADntCharacter::GetSpellPoints_Implementation() const
{
	ADntPlayerState* DntPlayerState = GetPlayerState<ADntPlayerState>();
	check(DntPlayerState);
	return DntPlayerState->GetSpellPoints();
}

int32 ADntCharacter::GetPlayerLevel_Implementation()
{
	const ADntPlayerState* DntPlayerState = GetPlayerState<ADntPlayerState>();
	check(DntPlayerState);
	return DntPlayerState->GetPlayerLevel();
}

void ADntCharacter::InitAbilityActorInfo()
{
	ADntPlayerState* DntPlayerState = GetPlayerState<ADntPlayerState>();
	check(DntPlayerState);
	DntPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(DntPlayerState,this);	
	Cast<UDntAbilitySystemComponent>(DntPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = DntPlayerState->GetAbilitySystemComponent();
	AttributeSet = DntPlayerState->GetAttributeSet();
	OnAscRegistered.Broadcast(AbilitySystemComponent);
	
	if (ADntPlayerController* DntPlayerController = Cast<ADntPlayerController>(GetController()))
	{
		if (ADntHUD* DntHUD = Cast<ADntHUD>(DntPlayerController->GetHUD()))
		{
			DntHUD->InitOverlay(DntPlayerController,DntPlayerState,AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}


