// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */

struct FDntGameplayTags
{
public:
	static const FDntGameplayTags& Get(){return GameplayTags;}
	static void InitializeNativeGameplayTags();
	// 核心五维 + 精神力
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;
	FGameplayTag Attributes_Primary_ManaVigor;
	FGameplayTag Attributes_Primary_Luck;
	FGameplayTag Attributes_Primary_Spirit;

// 衍生战斗属性
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_MaxStamina;
	FGameplayTag Attributes_Secondary_MaxSanity;
	FGameplayTag Attributes_Secondary_MaxHunger;
	FGameplayTag Attributes_Secondary_AttackDamage;
	FGameplayTag Attributes_Secondary_AbilityPower;
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_MagicResistance;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_ArmorPenPercent;
	FGameplayTag Attributes_Secondary_MagicPenetration;
	FGameplayTag Attributes_Secondary_MagicPenPercent;
	FGameplayTag Attributes_Secondary_CritChance;
	FGameplayTag Attributes_Secondary_MagicalCritChance;
	FGameplayTag Attributes_Secondary_CritDamage;
	FGameplayTag Attributes_Secondary_LifeSteal;
	FGameplayTag Attributes_Secondary_Omnivamp;
	FGameplayTag Attributes_Secondary_SpellVamp;
	FGameplayTag Attributes_Secondary_MoveSpeed;
	FGameplayTag Attributes_Secondary_AttackSpeed;
	FGameplayTag Attributes_Secondary_AttackRange;
	FGameplayTag Attributes_Secondary_AbilityHaste;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_HealAndShieldPower;
	FGameplayTag Attributes_Secondary_OnHitDamagePhys;
	FGameplayTag Attributes_Secondary_OnHitDamageMag;
	FGameplayTag Attributes_Secondary_OnHitDamagePctPhys;
	FGameplayTag Attributes_Secondary_OnHitDamagePctMag;
	FGameplayTag Attributes_Secondary_ProcCounter;
	FGameplayTag Attributes_Secondary_Gold;

// 实时状态资源
	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_Mana;
	FGameplayTag Attributes_Vital_Stamina;
	FGameplayTag Attributes_Vital_Sanity;
	FGameplayTag Attributes_Vital_Hunger;

// 抗性属性
	FGameplayTag Attributes_Resistance_FireResistance;
	FGameplayTag Attributes_Resistance_LightningResistance;
	FGameplayTag Attributes_Resistance_ArcaneResistance;
	FGameplayTag Attributes_Resistance_PhysicalResistance;
	FGameplayTag Attributes_Resistance_Tenacity;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
private:
	static FDntGameplayTags GameplayTags;
};
