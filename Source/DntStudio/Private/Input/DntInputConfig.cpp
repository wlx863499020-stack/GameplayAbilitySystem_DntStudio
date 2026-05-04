// DntStudio


#include "Input/DntInputConfig.h"

const UInputAction* UDntInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FDntInputAction& Action: AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp,Error, TEXT("000[%s],on[%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
