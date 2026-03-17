// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "DntInputConfig.h"
#include "EnhancedInputComponent.h"
#include "DntInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class DNTSTUDIO_API UDntInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class  UserClass,typename PressedFuncType,typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UDntInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType RealeasedFunc, HeldFuncType HeldFunc);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UDntInputComponent::BindAbilityActions(const UDntInputConfig* InputConfig, UserClass* Object,PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check (InputConfig);
	
	for (const FDntInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Started,Object,PressedFunc,Action.InputTag);
			}
			
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Completed,Object,ReleasedFunc,Action.InputTag);
			}
			
			if (HeldFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Triggered,Object,HeldFunc,Action.InputTag);
			}
		}
	}
	
}
