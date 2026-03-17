// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DntGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class DNTSTUDIO_API UDntGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;
};
