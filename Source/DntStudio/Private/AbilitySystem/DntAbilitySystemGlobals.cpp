// DntStudio


#include "AbilitySystem/DntAbilitySystemGlobals.h"

#include "DntAbilityTypes.h"

FGameplayEffectContext* UDntAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FDntGameplayEffectContext();
	
}
