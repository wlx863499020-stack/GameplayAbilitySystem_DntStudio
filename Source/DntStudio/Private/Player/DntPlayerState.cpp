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
	
	SetNetUpdateFrequency(100.f);
}

void ADntPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ADntPlayerState, Level);
	DOREPLIFETIME(ADntPlayerState, XP);
	DOREPLIFETIME(ADntPlayerState, AttributePoints);
	DOREPLIFETIME(ADntPlayerState, SpellPoints);	
}

UAbilitySystemComponent* ADntPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ADntPlayerState::AddToXP(int32 InXP)
{
	XP += InXP;
	OnXPChangeDelegate.Broadcast(XP);
}

void ADntPlayerState::AddToLevel(int32 InLevel)
{
	Level += InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void ADntPlayerState::AddToAttributePoints(int32 InPoints)
{
	AttributePoints += InPoints;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void ADntPlayerState::AddToSpellPoints(int32 InPoints)
{
	SpellPoints += InPoints;
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

void ADntPlayerState::SetXP(int32 InXP)
{
	XP = InXP;
	OnXPChangeDelegate.Broadcast(XP);
}

void ADntPlayerState::SetLevel(int32 InLevel)
{
	Level = InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void ADntPlayerState::OnRep_Level(int32 OldLevel) 
{
	OnLevelChangedDelegate.Broadcast(Level);
}

void ADntPlayerState::OnRep_XP(int32 OldXP) 
{
	OnXPChangeDelegate.Broadcast(XP);
}

void ADntPlayerState::OnRep_AttributePoints(int32 OldAttributePoints)
{
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void ADntPlayerState::OnRep_SpellPoints(int32 OldSpellPoints)
{
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}
