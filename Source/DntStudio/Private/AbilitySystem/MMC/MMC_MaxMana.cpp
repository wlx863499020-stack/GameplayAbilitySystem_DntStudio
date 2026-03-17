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
	
	ICombatInterface* CombatInterface = Cast <ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();
	
	return 50.f + ManaVigor + 10.f*PlayerLevel;
	
}
