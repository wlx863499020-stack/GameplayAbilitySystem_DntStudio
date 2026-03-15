// DntStudio


#include "Player/DntPlayerState.h"

#include "AbilitySystem/DntAbilitySystemComponent.h"
#include "AbilitySystem/DntAttributeSet.h"
#include "Net/UnrealNetwork.h"

ADntPlayerState::ADntPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UDntAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UDntAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100.f	;
}

void ADntPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ADntPlayerState, Level);
}

UAbilitySystemComponent* ADntPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ADntPlayerState::OnRep_Level(int32 OldLevel) const
{
	
}
