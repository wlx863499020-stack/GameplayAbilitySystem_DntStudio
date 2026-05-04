// DntStudio


#include "AbilitySystem/MMC/MMC_MaxMana.h"

#include "AbilitySystem/DntAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	ManaVigorDef.AttributeToCapture = UDntAttributeSet::GetIntelligenceAttribute();
	ManaVigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ManaVigorDef.bSnapshot = false;
	
	RelevantAttributesToCapture.Add(ManaVigorDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float ManaVigor = 0.f;
	GetCapturedAttributeMagnitude(ManaVigorDef,Spec,EvaluateParameters,ManaVigor);
	ManaVigor = FMath::Max<float>(ManaVigor,0.f);
	
	int32 PlayerLevel = 1;
	if (Spec.GetContext().GetSourceObject()->Implements<UCombatInterface>())
	{
		PlayerLevel = ICombatInterface::Execute_GetPlayerLevel(Spec.GetContext().GetSourceObject());
	}
	
	return 50.f + ManaVigor + 10.f*PlayerLevel;
	
}
