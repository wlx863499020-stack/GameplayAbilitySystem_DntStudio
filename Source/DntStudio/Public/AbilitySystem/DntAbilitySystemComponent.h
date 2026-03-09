// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DntAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class DNTSTUDIO_API UDntAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();
	
	protected:
	
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
