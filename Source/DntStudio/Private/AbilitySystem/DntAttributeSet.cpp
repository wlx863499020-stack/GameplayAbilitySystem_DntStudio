// DntStudio


#include "AbilitySystem/DntAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "DntGameplayTags.h"

UDntAttributeSet::UDntAttributeSet()
{
	const FDntGameplayTags& GameplayTags = FDntGameplayTags::Get();
	

	// 核心五维 + 精神力
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Resilience, GetResilienceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Vigor, GetVigorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_ManaVigor, GetManaVigorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Luck, GetLuckAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Spirit, GetSpiritAttribute);

	// 衍生战斗属性
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);
	
	
}
    //*********************************************************************************************

    ////TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength,GetStrengthAttribute);

    //DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet,Health,COND_None,REPNOTIFY_Always);

    //void UDntAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
    //{GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet,Health,OldHealth)}
    //**********************************************************************************************


void UDntAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
    /*
	 * Primary Attributes (核心五维护 + 精神力)  Strength, Intelligence, Resilience, Vigor, Luck, Spirit
	 */
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, ManaVigor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Luck, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Spirit, COND_None, REPNOTIFY_Always);

	/*
	 *Secondary Attributes (衍生战斗属性)AttackDamage, AbilityPower, Armor, MagicResistance,
	 *ArmorPenetration, ArmorPenPercent, MagicPenetration, MagicPenPercent,CritChance, 
	 *MagicalCritChance, CritDamage, Omnivamp, SpellVamp,AttackSpeed, AttackRange, AbilityHaste, Gold
	 */
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, MaxSanity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, MaxHunger, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, AttackDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, AbilityPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, MagicResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, ArmorPenPercent, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, MagicPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, MagicPenPercent, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, CritChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, MagicalCritChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, CritDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Omnivamp, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, SpellVamp, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, AttackRange, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, AbilityHaste, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, HealAndShieldPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, OnHitDamagePhys, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, OnHitDamageMag, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, OnHitDamagePctPhys, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, OnHitDamagePctMag, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, ProcCounter, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Gold, COND_None, REPNOTIFY_Always);

	/*
	 * Vital Attributes (实时状态资源)Health, Mana, Stamina, Sanity, Hunger
	 */
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Sanity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Hunger, COND_None, REPNOTIFY_Always);

	/*
	 * Resistance Attributes (抗性属性)FireResistance, LightningResistance, ArcaneResistance, PhysicalResistance, Tenacity
	 */
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, FireResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, LightningResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, ArcaneResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, PhysicalResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Tenacity, COND_None, REPNOTIFY_Always);
}

void UDntAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UDntAttributeSet::SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	//Source = causer
	
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast <ACharacter>(Props.SourceController->GetPawn());
		}
	}
	
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props. TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UDntAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	FEffectProperties Props;
	SetEffectProperties(Data, Props);
	
    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
    	SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
    	UE_LOG(LogTemp,Warning, TEXT("Changed %s, on : %f"), *Props.TargetAvatarActor->GetName(),GetHealth());
    }
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
}

/*
 * 一、 Primary Attributes (基础属性)
 */
void UDntAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Strength, OldStrength);
}

void UDntAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Intelligence, OldIntelligence);
}

void UDntAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Resilience, OldResilience);
}

void UDntAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Vigor, OldVigor);
}

void UDntAttributeSet::OnRep_ManaVigor(const FGameplayAttributeData& OldManaVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Vigor, OldManaVigor);
}

void UDntAttributeSet::OnRep_Luck(const FGameplayAttributeData& OldLuck) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Luck, OldLuck);
}

void UDntAttributeSet::OnRep_Spirit(const FGameplayAttributeData& OldSpirit) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Spirit, OldSpirit);
}

/*
 * 二、 Secondary Attributes (衍生战斗属性)
 */
void UDntAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, MaxHealth, OldMaxHealth);
}

void UDntAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, MaxMana, OldMaxMana);
}

void UDntAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, MaxStamina, OldMaxStamina);
}

void UDntAttributeSet::OnRep_MaxSanity(const FGameplayAttributeData& OldMaxSanity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, MaxSanity, OldMaxSanity);
}

void UDntAttributeSet::OnRep_MaxHunger(const FGameplayAttributeData& OldMaxHunger) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, MaxHunger, OldMaxHunger);
}

void UDntAttributeSet::OnRep_AttackDamage(const FGameplayAttributeData& OldAttackDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, AttackDamage, OldAttackDamage);
}

void UDntAttributeSet::OnRep_AbilityPower(const FGameplayAttributeData& OldAbilityPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, AbilityPower, OldAbilityPower);
}

void UDntAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Armor, OldArmor);
}

void UDntAttributeSet::OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, MagicResistance, OldMagicResistance);
}

void UDntAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UDntAttributeSet::OnRep_ArmorPenPercent(const FGameplayAttributeData& OldArmorPenPercent) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, ArmorPenPercent, OldArmorPenPercent);
}

void UDntAttributeSet::OnRep_MagicPenetration(const FGameplayAttributeData& OldMagicPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, MagicPenetration, OldMagicPenetration);
}

void UDntAttributeSet::OnRep_MagicPenPercent(const FGameplayAttributeData& OldMagicPenPercent) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, MagicPenPercent, OldMagicPenPercent);
}

void UDntAttributeSet::OnRep_CritChance(const FGameplayAttributeData& OldCritChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, CritChance, OldCritChance);
}

void UDntAttributeSet::OnRep_MagicalCritChance(const FGameplayAttributeData& OldMagicalCritChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, MagicalCritChance, OldMagicalCritChance);
}

void UDntAttributeSet::OnRep_CritDamage(const FGameplayAttributeData& OldCritDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, CritDamage, OldCritDamage);
}

void UDntAttributeSet::OnRep_Omnivamp(const FGameplayAttributeData& OldOmnivamp) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Omnivamp, OldOmnivamp);
}

void UDntAttributeSet::OnRep_SpellVamp(const FGameplayAttributeData& OldSpellVamp) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, SpellVamp, OldSpellVamp);
}

void UDntAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, AttackSpeed, OldAttackSpeed);
}

void UDntAttributeSet::OnRep_AttackRange(const FGameplayAttributeData& OldAttackRange) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, AttackRange, OldAttackRange);
}

void UDntAttributeSet::OnRep_AbilityHaste(const FGameplayAttributeData& OldAbilityHaste) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, AbilityHaste, OldAbilityHaste);
}

void UDntAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const 
{ 
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, HealthRegeneration, OldHealthRegeneration); 
}

void UDntAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const 
{ 
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, ManaRegeneration, OldManaRegeneration); 
}

void UDntAttributeSet::OnRep_HealAndShieldPower(const FGameplayAttributeData& OldHealAndShieldPower) const 
{ 
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, HealAndShieldPower, OldHealAndShieldPower); 
}

void UDntAttributeSet::OnRep_Gold(const FGameplayAttributeData& OldGold) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Gold, OldGold);
}

void UDntAttributeSet::OnRep_OnHitDamagePhys(const FGameplayAttributeData& OldOnHitDamagePhys) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, OnHitDamagePhys, OldOnHitDamagePhys);
}

void UDntAttributeSet::OnRep_OnHitDamageMag(const FGameplayAttributeData& OldOnHitDamageMag) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, OnHitDamageMag, OldOnHitDamageMag);
}

void UDntAttributeSet::OnRep_OnHitDamagePctPhys(const FGameplayAttributeData& OldOnHitDamagePctPhys) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, OnHitDamagePctPhys, OldOnHitDamagePctPhys);
}

void UDntAttributeSet::OnRep_OnHitDamagePctMag(const FGameplayAttributeData& OldOnHitDamagePctMag) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, OnHitDamagePctMag, OldOnHitDamagePctMag);
}

void UDntAttributeSet::OnRep_ProcCounter(const FGameplayAttributeData& OldProcCounter) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, ProcCounter, OldProcCounter);
}

/*
 * 三、 Vital Attributes (实时状态资源)
 */
void UDntAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Health, OldHealth);
}

void UDntAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Mana, OldMana);
}

void UDntAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Stamina, OldStamina);
}

void UDntAttributeSet::OnRep_Sanity(const FGameplayAttributeData& OldSanity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Sanity, OldSanity);
}

void UDntAttributeSet::OnRep_Hunger(const FGameplayAttributeData& OldHunger) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Hunger, OldHunger);
}

/*
 * 四、 Resistance Attributes (抗性与韧性)
 */

void UDntAttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, FireResistance, OldFireResistance);
}

void UDntAttributeSet::OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, LightningResistance, OldLightningResistance);
}

void UDntAttributeSet::OnRep_ArcaneResistance(const FGameplayAttributeData& OldArcaneResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, ArcaneResistance, OldArcaneResistance);
}

void UDntAttributeSet::OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, PhysicalResistance, OldPhysicalResistance);
}

void UDntAttributeSet::OnRep_Tenacity(const FGameplayAttributeData& OldTenacity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Tenacity, OldTenacity);
}


