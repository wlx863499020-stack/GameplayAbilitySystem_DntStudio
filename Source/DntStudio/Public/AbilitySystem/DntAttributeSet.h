// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DntAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)



USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	
	FEffectProperties(){}
	
	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;
	
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;
	
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

//
//typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPrt;
template<class T>
using TStaticFunPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;


/**
 * 
 */
UCLASS()
class DNTSTUDIO_API UDntAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UDntAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	
	TMap<FGameplayTag, 	TStaticFunPtr<FGameplayAttribute()>> TagsToAttributes;
	

	
	
	
	//*************************************************************************************************
	//UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health,Category="Vital Attributes")
	//FGameplayAttributeData Health;
	//ATTRIBUTE_ACCESSORS(UDntAttributeSet, Health);
	
	//UFUNCTION()
	//void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	//*************************************************************************************************
	
	/*
	 * Primary Attributes    Strength, Intelligence, Resilience, Vigor, Luck, Spirit
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength; ATTRIBUTE_ACCESSORS(UDntAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence; ATTRIBUTE_ACCESSORS(UDntAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
	FGameplayAttributeData Resilience; ATTRIBUTE_ACCESSORS(UDntAttributeSet, Resilience);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
	FGameplayAttributeData Vigor; ATTRIBUTE_ACCESSORS(UDntAttributeSet, Vigor);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaVigor, Category = "Primary Attributes")
	FGameplayAttributeData ManaVigor; ATTRIBUTE_ACCESSORS(UDntAttributeSet, ManaVigor);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Luck, Category = "Primary Attributes")
	FGameplayAttributeData Luck; ATTRIBUTE_ACCESSORS(UDntAttributeSet, Luck);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Spirit, Category = "Primary Attributes")
	FGameplayAttributeData Spirit; ATTRIBUTE_ACCESSORS(UDntAttributeSet, Spirit);

	/*
	 *Secondary Attributes (衍生战斗属性)AttackDamage, AbilityPower, Armor, MagicResistance,
	 *ArmorPenetration, ArmorPenPercent, MagicPenetration, MagicPenPercent,CritChance, 
	 *MagicalCritChance, CriticalHitDamage, Omnivamp, SpellVamp,AttackSpeed, AttackRange, AbilityHaste, 
	 *HealthRegeneration ManaRegeneration HealAndShieldPower Gold
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Secondary Attributes")
	FGameplayAttributeData MaxHealth; ATTRIBUTE_ACCESSORS(UDntAttributeSet, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Attributes")
	FGameplayAttributeData MaxMana; ATTRIBUTE_ACCESSORS(UDntAttributeSet, MaxMana);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Secondary Attributes")
	FGameplayAttributeData MaxStamina; ATTRIBUTE_ACCESSORS(UDntAttributeSet, MaxStamina);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxSanity, Category = "Secondary Attributes")
	FGameplayAttributeData MaxSanity; ATTRIBUTE_ACCESSORS(UDntAttributeSet, MaxSanity);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHunger, Category = "Secondary Attributes")
	FGameplayAttributeData MaxHunger; ATTRIBUTE_ACCESSORS(UDntAttributeSet, MaxHunger);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackDamage, Category = "Secondary Attributes")
	FGameplayAttributeData AttackDamage; ATTRIBUTE_ACCESSORS(UDntAttributeSet, AttackDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AbilityPower, Category = "Secondary Attributes")
	FGameplayAttributeData AbilityPower; ATTRIBUTE_ACCESSORS(UDntAttributeSet, AbilityPower);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor; ATTRIBUTE_ACCESSORS(UDntAttributeSet, Armor);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicResistance, Category = "Secondary Attributes")
	FGameplayAttributeData MagicResistance; ATTRIBUTE_ACCESSORS(UDntAttributeSet, MagicResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration; ATTRIBUTE_ACCESSORS(UDntAttributeSet, ArmorPenetration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenPercent, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenPercent; ATTRIBUTE_ACCESSORS(UDntAttributeSet, ArmorPenPercent);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData MagicPenetration; ATTRIBUTE_ACCESSORS(UDntAttributeSet, MagicPenetration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicPenPercent, Category = "Secondary Attributes")
	FGameplayAttributeData MagicPenPercent; ATTRIBUTE_ACCESSORS(UDntAttributeSet, MagicPenPercent);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritChance, Category = "Secondary Attributes")
	FGameplayAttributeData CritChance; ATTRIBUTE_ACCESSORS(UDntAttributeSet, CritChance);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Attributes")
	FGameplayAttributeData BlockChance; ATTRIBUTE_ACCESSORS(UDntAttributeSet, BlockChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicalCritChance, Category = "Secondary Attributes")
	FGameplayAttributeData MagicalCritChance; ATTRIBUTE_ACCESSORS(UDntAttributeSet, MagicalCritChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage; ATTRIBUTE_ACCESSORS(UDntAttributeSet, CriticalHitDamage);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance; ATTRIBUTE_ACCESSORS(UDntAttributeSet, CriticalHitResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Omnivamp, Category = "Secondary Attributes")
	FGameplayAttributeData Omnivamp; ATTRIBUTE_ACCESSORS(UDntAttributeSet, Omnivamp);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LifeSteal, Category = "Secondary Attributes")
	FGameplayAttributeData LifeSteal; ATTRIBUTE_ACCESSORS(UDntAttributeSet, LifeSteal);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_SpellVamp, Category = "Secondary Attributes")
	FGameplayAttributeData SpellVamp; ATTRIBUTE_ACCESSORS(UDntAttributeSet, SpellVamp);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackSpeed, Category = "Secondary Attributes")
	FGameplayAttributeData AttackSpeed; ATTRIBUTE_ACCESSORS(UDntAttributeSet, AttackSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackRange, Category = "Secondary Attributes")
	FGameplayAttributeData AttackRange; ATTRIBUTE_ACCESSORS(UDntAttributeSet, AttackRange);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AbilityHaste, Category = "Secondary Attributes")
	FGameplayAttributeData AbilityHaste; ATTRIBUTE_ACCESSORS(UDntAttributeSet, AbilityHaste);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration; ATTRIBUTE_ACCESSORS(UDntAttributeSet, HealthRegeneration);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration; ATTRIBUTE_ACCESSORS(UDntAttributeSet, ManaRegeneration);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealAndShieldPower, Category = "Secondary Attributes")
	FGameplayAttributeData HealAndShieldPower; ATTRIBUTE_ACCESSORS(UDntAttributeSet, HealAndShieldPower);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_OnHitDamagePhys, Category = "Secondary Attributes")
	FGameplayAttributeData OnHitDamagePhys; ATTRIBUTE_ACCESSORS(UDntAttributeSet, OnHitDamagePhys);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_OnHitDamageMag, Category = "Secondary Attributes")
	FGameplayAttributeData OnHitDamageMag; ATTRIBUTE_ACCESSORS(UDntAttributeSet, OnHitDamageMag);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_OnHitDamagePctPhys, Category = "Secondary Attributes")
	FGameplayAttributeData OnHitDamagePctPhys; ATTRIBUTE_ACCESSORS(UDntAttributeSet, OnHitDamagePctPhys);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_OnHitDamagePctMag, Category = "Secondary Attributes")
	FGameplayAttributeData OnHitDamagePctMag; ATTRIBUTE_ACCESSORS(UDntAttributeSet, OnHitDamagePctMag);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ProcCounter, Category = "Secondary Attributes")
	FGameplayAttributeData ProcCounter; ATTRIBUTE_ACCESSORS(UDntAttributeSet, ProcCounter);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Gold, Category = "Secondary Attributes")
	FGameplayAttributeData Gold; ATTRIBUTE_ACCESSORS(UDntAttributeSet, Gold);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Tenacity, Category = "Resistance Attributes")
	FGameplayAttributeData Tenacity; ATTRIBUTE_ACCESSORS(UDntAttributeSet, Tenacity);

	/*
	 * Vital Attributes (实时状态资源) Health, Mana, Stamina, Sanity, Hunger,
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health; ATTRIBUTE_ACCESSORS(UDntAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana; ATTRIBUTE_ACCESSORS(UDntAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Vital Attributes")
	FGameplayAttributeData Stamina; ATTRIBUTE_ACCESSORS(UDntAttributeSet, Stamina);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Sanity, Category = "Vital Attributes")
	FGameplayAttributeData Sanity; ATTRIBUTE_ACCESSORS(UDntAttributeSet, Sanity);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Hunger, Category = "Vital Attributes")
	FGameplayAttributeData Hunger; ATTRIBUTE_ACCESSORS(UDntAttributeSet, Hunger);


	/*
	 * Resistance Attributes (抗性属性)TrueResistance, ArcaneResistance, PhysicalResistance,
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_TrueResistance, Category = "Resistance Attributes")
	FGameplayAttributeData TrueResistance; ATTRIBUTE_ACCESSORS(UDntAttributeSet, TrueResistance);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArcaneResistance, Category = "Resistance Attributes")
	FGameplayAttributeData ArcaneResistance; ATTRIBUTE_ACCESSORS(UDntAttributeSet, ArcaneResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalResistance, Category = "Resistance Attributes")
	FGameplayAttributeData PhysicalResistance; ATTRIBUTE_ACCESSORS(UDntAttributeSet, PhysicalResistance);
	

	/*
	 * 五、 Meta Attributes (元属性管道) IncomingDamage, IncomingXP, IncomingGold
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage; ATTRIBUTE_ACCESSORS(UDntAttributeSet, IncomingDamage);

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingXP; ATTRIBUTE_ACCESSORS(UDntAttributeSet, IncomingXP);

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
		FGameplayAttributeData IncomingGold; ATTRIBUTE_ACCESSORS(UDntAttributeSet, IncomingGold);
	
/* Primary OnReps */
UFUNCTION() void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;                   // 力量
UFUNCTION() void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;           // 智力
UFUNCTION() void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;               // 韧性
UFUNCTION() void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;                         // 活力
UFUNCTION() void OnRep_ManaVigor(const FGameplayAttributeData& OldVigor) const;                     // 法力活力
UFUNCTION() void OnRep_Luck(const FGameplayAttributeData& OldLuck) const;                           // 幸运
UFUNCTION() void OnRep_Spirit(const FGameplayAttributeData& OldSpirit) const;                       // 精神

/* Secondary OnReps */
UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;                 // 最大生命值
UFUNCTION() void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;                     // 最大法力值
UFUNCTION() void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;               // 最大体力值
UFUNCTION() void OnRep_MaxSanity(const FGameplayAttributeData& OldMaxSanity) const;                 // 最大理智值
UFUNCTION() void OnRep_MaxHunger(const FGameplayAttributeData& OldMaxHunger) const;                 // 最大饥饿值
UFUNCTION() void OnRep_AttackDamage(const FGameplayAttributeData& OldAttackDamage) const;           // 攻击力
UFUNCTION() void OnRep_AbilityPower(const FGameplayAttributeData& OldAbilityPower) const;           // 法术强度
UFUNCTION() void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;                         // 护甲
UFUNCTION() void OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance) const;     // 魔法抗性
UFUNCTION() void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;   // 护甲穿透
UFUNCTION() void OnRep_ArmorPenPercent(const FGameplayAttributeData& OldArmorPenPercent) const;     // 百分比护甲穿透
UFUNCTION() void OnRep_MagicPenetration(const FGameplayAttributeData& OldMagicPenetration) const;   // 法术穿透
UFUNCTION() void OnRep_MagicPenPercent(const FGameplayAttributeData& OldMagicPenPercent) const;     // 百分比法术穿透
UFUNCTION() void OnRep_CritChance(const FGameplayAttributeData& OldCritChance) const;               // 暴击率
UFUNCTION() void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;             // 格挡率
UFUNCTION() void OnRep_MagicalCritChance(const FGameplayAttributeData& OldMagicalCritChance) const; // 法术暴击率
UFUNCTION() void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const; // 暴击伤害
UFUNCTION() void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const; // 暴击抗性
UFUNCTION() void OnRep_Omnivamp(const FGameplayAttributeData& OldOmnivamp) const;                   // 全能吸血
UFUNCTION() void OnRep_LifeSteal(const FGameplayAttributeData& OldLifeSteal) const;                 // 物理吸血
UFUNCTION() void OnRep_SpellVamp(const FGameplayAttributeData& OldSpellVamp) const;                 // 法术吸血
UFUNCTION() void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const;             // 攻击速度
UFUNCTION() void OnRep_AttackRange(const FGameplayAttributeData& OldAttackRange) const;             // 攻击距离
UFUNCTION() void OnRep_AbilityHaste(const FGameplayAttributeData& OldAbilityHaste) const;           // 技能急速
UFUNCTION() void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const; // 生命回复
UFUNCTION() void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;   // 法力回复
UFUNCTION() void OnRep_HealAndShieldPower(const FGameplayAttributeData& OldHealAndShieldPower) const; // 治疗护盾强度
UFUNCTION() void OnRep_OnHitDamagePhys(const FGameplayAttributeData& OldOnHitDamagePhys) const;     // 普攻物理附加伤害
UFUNCTION() void OnRep_OnHitDamageMag(const FGameplayAttributeData& OldOnHitDamageMag) const;       // 普攻魔法附加伤害
UFUNCTION() void OnRep_OnHitDamagePctPhys(const FGameplayAttributeData& OldOnHitDamagePctPhys) const; // 普攻百分比物理伤害
UFUNCTION() void OnRep_OnHitDamagePctMag(const FGameplayAttributeData& OldOnHitDamagePctMag) const; // 普攻百分比魔法伤害
UFUNCTION() void OnRep_ProcCounter(const FGameplayAttributeData& OldProcCounter) const;             // 触发计数器
UFUNCTION() void OnRep_Gold(const FGameplayAttributeData& OldGold) const;                           // 金币
UFUNCTION() void OnRep_Tenacity(const FGameplayAttributeData& OldTenacity) const;                   // 韧性

/* Vital OnReps */
UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldHealth) const;                       // 生命值
UFUNCTION() void OnRep_Mana(const FGameplayAttributeData& OldMana) const;                           // 法力值
UFUNCTION() void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;                     // 体力值
UFUNCTION() void OnRep_Sanity(const FGameplayAttributeData& OldSanity) const;                       // 理智值
UFUNCTION() void OnRep_Hunger(const FGameplayAttributeData& OldHunger) const;                       // 饥饿值

/* Resistance OnReps */
UFUNCTION() void OnRep_TrueResistance(const FGameplayAttributeData& OldTrueResistance) const;         // 真实伤害抗性
UFUNCTION() void OnRep_ArcaneResistance(const FGameplayAttributeData& OldArcaneResistance) const;     // 奥术抗性
UFUNCTION() void OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const; // 物理抗性

	
private:
	void HandleIncomingDamage(const FEffectProperties& Props);
	void HandleIncomingXP(const FEffectProperties& Props);
	void Debuff(const FEffectProperties& Props);
	void SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
	void ShowFloatingText(const FEffectProperties& Props,float Damage, bool bBlockedHit, bool bCriticalHit) const;
	void SendXPEvent(const FEffectProperties& Props);
	bool bTopOffHealth = false;
	bool bTopOffMana = false;
};
