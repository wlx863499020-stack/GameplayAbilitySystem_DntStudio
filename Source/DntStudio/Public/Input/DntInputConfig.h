// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DntInputConfig.generated.h"

USTRUCT(BlueprintType)
struct  FDntInputAction
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;
	
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};


/**
 * 
 */
UCLASS()
class DNTSTUDIO_API UDntInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag,bool bLogNotFound = false) const;
	
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FDntInputAction> AbilityInputActions;
	
	
};
