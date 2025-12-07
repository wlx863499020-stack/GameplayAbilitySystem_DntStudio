// DntStudio


#include "Player/DntPlayerState.h"

#include "AbilitySystem/DntAbilitySystemComponent.h"
#include "AbilitySystem/DntAttributeSet.h"

ADntPlayerState::ADntPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UDntAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UDntAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100.f	;
}

UAbilitySystemComponent* ADntPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
