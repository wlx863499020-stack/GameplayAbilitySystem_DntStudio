// DntStudio


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/DntAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallBacksToDependencies()
{
	UDntAttributeSet* AS = CastChecked<UDntAttributeSet>(AttributeSet);
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
	[this, Pair](const FOnAttributeChangeData& Data)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}	
	);
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UDntAttributeSet* AS = CastChecked<UDntAttributeSet>(AttributeSet);
	check(AttributeInfo);
	
	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
	
	
	
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,const FGameplayAttribute& Attribute) const
{
	FDntAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
