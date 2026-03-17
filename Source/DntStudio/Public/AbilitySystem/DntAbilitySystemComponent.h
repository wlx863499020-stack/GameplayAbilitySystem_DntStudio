// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DntAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&/*AssetTags*/);

/**
 * 
 */
UCLASS()
class DNTSTUDIO_API UDntAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();
	
	
	FEffectAssetTags EffectAssetTags;
	
void AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	

protected:
	
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
