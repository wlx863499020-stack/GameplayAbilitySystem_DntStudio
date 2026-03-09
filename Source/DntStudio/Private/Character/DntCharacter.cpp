// DntStudio


#include "Character/DntCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/DntAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/DntPlayerController.h"
#include "Player/DntPlayerState.h"
#include "UI/HUD/DntHUD.h"

ADntCharacter::ADntCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void ADntCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
//init ability actor info for the server
	 InitAbilityActorInfo();

}

void ADntCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Init ability actor info for the client
    InitAbilityActorInfo();
}

void ADntCharacter::InitAbilityActorInfo()
{
	ADntPlayerState* DntPlayerState = GetPlayerState<ADntPlayerState>();
	check(DntPlayerState);
	DntPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(DntPlayerState,this);	
	Cast<UDntAbilitySystemComponent>(DntPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = DntPlayerState->GetAbilitySystemComponent();
	AttributeSet = DntPlayerState->GetAttributeSet();
	
	if (ADntPlayerController* DntPlayerController = Cast<ADntPlayerController>(GetController()))
	{
		if (ADntHUD* DntHUD = Cast<ADntHUD>(DntPlayerController->GetHUD()))
		{
			DntHUD->InitOverlay(DntPlayerController,DntPlayerState,AbilitySystemComponent, AttributeSet);
		}
	}
}
