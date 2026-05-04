// DntStudio


#include "UI/WidgetController/DntWidgetController.h"

#include "AbilitySystem/DntAbilitySystemComponent.h"
#include "AbilitySystem/DntAttributeSet.h"
#include "Player/DntPlayerController.h"
#include "Player/DntPlayerState.h"
#include "AbilitySystem/Data/AbilityInfo.h"

void UDntWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UDntWidgetController::BroadcastInitialValues()
{
	
}

void UDntWidgetController::BindCallbacksToDependencies()
{
	
}

void UDntWidgetController::BroadcastAbilityInfo()
{
	if (!GetDntASC()->bStartupAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this](const FGameplayAbilitySpec& AbilitySpec)
	{
		FDntAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(DntAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));/////////////
		Info.InputTag = DntAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
		Info.StatusTag = DntAbilitySystemComponent->GetStatusFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});

	GetDntASC()->ForEachAbility(BroadcastDelegate);
}

ADntPlayerController* UDntWidgetController::GetDntPC()
{
	if (DntPlayerController == nullptr)
	{
		DntPlayerController = Cast<ADntPlayerController>(PlayerController);
	}
	return DntPlayerController;
}

ADntPlayerState* UDntWidgetController::GetDntPS()
{
	if (DntPlayerState == nullptr)
	{
		DntPlayerState = Cast<ADntPlayerState>(PlayerState);
	}
	return DntPlayerState;
}

UDntAbilitySystemComponent* UDntWidgetController::GetDntASC()
{
	if (DntAbilitySystemComponent == nullptr)
	{
		DntAbilitySystemComponent = Cast<UDntAbilitySystemComponent>(AbilitySystemComponent);
	}
	return DntAbilitySystemComponent;
}

UDntAttributeSet* UDntWidgetController::GetDntAS()
{
	if (DntAttributeSet == nullptr)
	{
		DntAttributeSet = Cast<UDntAttributeSet>(AttributeSet);
	}
	return DntAttributeSet;
}

