// DntStudio

#include "DntGameplayTags.h"
#include "GameplayTagsManager.h"

FDntGameplayTags FDntGameplayTags::GameplayTags;

void FDntGameplayTags::InitializeNativeGameplayTags()
{
	// --- 核心五维 + 精神力 ---
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),
		TEXT("1")
	);

	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),
		TEXT("1")
	);

	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"),
		TEXT("1")
	);

	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"),
		TEXT("1")
	);

	GameplayTags.Attributes_Primary_ManaVigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.ManaVigor"),
		TEXT("1")
	);

	GameplayTags.Attributes_Primary_Luck = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Luck"),
		TEXT("1")
	);

	GameplayTags.Attributes_Primary_Spirit = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Spirit"),
		TEXT("1")
	);

	// --- 衍生战斗属性 ---
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_MaxStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxStamina"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_MaxSanity = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxSanity"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_MaxHunger = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHunger"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_AttackDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.AttackDamage"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_AbilityPower = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.AbilityPower"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_MagicResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MagicResistance"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_ArmorPenPercent = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenPercent"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_MagicPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MagicPenetration"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_MagicPenPercent = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MagicPenPercent"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_CritChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CritChance"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_MagicalCritChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MagicalCritChance"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_CritDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CritDamage"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_LifeSteal = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.LifeSteal"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_Omnivamp = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Omnivamp"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_SpellVamp = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.SpellVamp"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_MoveSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MoveSpeed"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_AttackSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.AttackSpeed"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_AttackRange = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.AttackRange"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_AbilityHaste = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.AbilityHaste"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_HealAndShieldPower = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealAndShieldPower"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_OnHitDamagePhys = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.OnHitDamagePhys"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_OnHitDamageMag = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.OnHitDamageMag"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_OnHitDamagePctPhys = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.OnHitDamagePctPhys"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_OnHitDamagePctMag = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.OnHitDamagePctMag"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_ProcCounter = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ProcCounter"),
		TEXT("1")
	);

	GameplayTags.Attributes_Secondary_Gold = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Gold"),
		TEXT("1")
	);

	// --- 实时状态资源 ---
	GameplayTags.Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.Health"),
		TEXT("1")
	);

	GameplayTags.Attributes_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.Mana"),
		TEXT("1")
	);

	GameplayTags.Attributes_Vital_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.Stamina"),
		TEXT("1")
	);

	GameplayTags.Attributes_Vital_Sanity = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.Sanity"),
		TEXT("1")
	);

	GameplayTags.Attributes_Vital_Hunger = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.Hunger"),
		TEXT("1")
	);

	// --- 抗性属性 ---
	GameplayTags.Attributes_Resistance_FireResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.FireResistance"),
		TEXT("1")
	);

	GameplayTags.Attributes_Resistance_LightningResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.LightningResistance"),
		TEXT("1")
	);

	GameplayTags.Attributes_Resistance_ArcaneResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.ArcaneResistance"),
		TEXT("1")
	);

	GameplayTags.Attributes_Resistance_PhysicalResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.PhysicalResistance"),
		TEXT("1")
	);

	GameplayTags.Attributes_Resistance_Tenacity = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Tenacity"),
		TEXT("1")
	);
	
	
	
	//****************Input*************************
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTags.LMB"),
	TEXT("1")
);
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTags.RMB"),
	TEXT("1")
);
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTags.1"),
	TEXT("1")
);
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTags.2"),
	TEXT("1")
);	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTags.3"),
	TEXT("1")
);
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
FName("InputTags.4"),
TEXT("1")
);
	
	
	
	
	
}