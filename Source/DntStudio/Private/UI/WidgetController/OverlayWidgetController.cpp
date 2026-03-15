// DntStudio


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/DntAbilitySystemComponent.h"
#include "AbilitySystem/DntAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UDntAttributeSet* DntAttributeSet = CastChecked<UDntAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(DntAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(DntAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(DntAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(DntAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallBacksToDependencies()
{
	const UDntAttributeSet* DntAttributeSet = CastChecked<UDntAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DntAttributeSet->GetHealthAttribute()).AddLambda(
		    [this](const FOnAttributeChangeData& Data)
		    {
		    	OnHealthChanged.Broadcast(Data.NewValue);
		    }	
		);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DntAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}	
	);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DntAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}	
	);
	
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DntAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}	
	);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DntAttributeSet->GetMaxManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnMaxManaChanged.Broadcast(Data.NewValue);
	}	
);

	
	Cast<UDntAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
	[this](const FGameplayTagContainer& AssetTags)
	{
		for (const FGameplayTag& Tag : AssetTags)
		{
			
			//
			FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
			if (Tag.MatchesTag(MessageTag))
			{
				const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				MessageWidgetRowSignature.Broadcast(*Row);
			}
		}
	}	
	);
}
