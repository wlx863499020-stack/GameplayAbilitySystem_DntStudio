// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "DntAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class DNTSTUDIO_API UDntAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
