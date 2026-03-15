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
	 *MagicalCritChance, CritDamage, Omnivamp, SpellVamp,AttackSpeed, AttackRange, AbilityHaste, 
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

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicalCritChance, Category = "Secondary Attributes")
	FGameplayAttributeData MagicalCritChance; ATTRIBUTE_ACCESSORS(UDntAttributeSet, MagicalCritChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CritDamage; ATTRIBUTE_ACCESSORS(UDntAttributeSet, CritDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Omnivamp, Category = "Secondary Attributes")
	FGameplayAttributeData Omnivamp; ATTRIBUTE_ACCESSORS(UDntAttributeSet, Omnivamp);

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
	 * Resistance Attributes (抗性属性)FireResistance, LightningResistance, ArcaneResistance, PhysicalResistance, Tenacity
	 */
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireResistance, Category = "Resistance Attributes")
	FGameplayAttributeData FireResistance; ATTRIBUTE_ACCESSORS(UDntAttributeSet, FireResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightningResistance, Category = "Resistance Attributes")
	FGameplayAttributeData LightningResistance; ATTRIBUTE_ACCESSORS(UDntAttributeSet, LightningResistance);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArcaneResistance, Category = "Resistance Attributes")
	FGameplayAttributeData ArcaneResistance; ATTRIBUTE_ACCESSORS(UDntAttributeSet, ArcaneResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalResistance, Category = "Resistance Attributes")
	FGameplayAttributeData PhysicalResistance; ATTRIBUTE_ACCESSORS(UDntAttributeSet, PhysicalResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Tenacity, Category = "Resistance Attributes")
	FGameplayAttributeData Tenacity; ATTRIBUTE_ACCESSORS(UDntAttributeSet, Tenacity);

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
	UFUNCTION() void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION() void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	UFUNCTION() void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	UFUNCTION() void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
	UFUNCTION() void OnRep_ManaVigor(const FGameplayAttributeData& OldVigor) const;
	UFUNCTION() void OnRep_Luck(const FGameplayAttributeData& OldLuck) const;
	UFUNCTION() void OnRep_Spirit(const FGameplayAttributeData& OldSpirit) const;

	/* Secondary OnReps */
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION() void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	UFUNCTION() void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;
	UFUNCTION() void OnRep_MaxSanity(const FGameplayAttributeData& OldMaxSanity) const;
	UFUNCTION() void OnRep_MaxHunger(const FGameplayAttributeData& OldMaxHunger) const;
	UFUNCTION() void OnRep_AttackDamage(const FGameplayAttributeData& OldAttackDamage) const;
	UFUNCTION() void OnRep_AbilityPower(const FGameplayAttributeData& OldAbilityPower) const;
	UFUNCTION() void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	UFUNCTION() void OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance) const;
	UFUNCTION() void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
	UFUNCTION() void OnRep_ArmorPenPercent(const FGameplayAttributeData& OldArmorPenPercent) const;
	UFUNCTION() void OnRep_MagicPenetration(const FGameplayAttributeData& OldMagicPenetration) const;
	UFUNCTION() void OnRep_MagicPenPercent(const FGameplayAttributeData& OldMagicPenPercent) const;
	UFUNCTION() void OnRep_CritChance(const FGameplayAttributeData& OldCritChance) const;
	UFUNCTION() void OnRep_MagicalCritChance(const FGameplayAttributeData& OldMagicalCritChance) const;
	UFUNCTION() void OnRep_CritDamage(const FGameplayAttributeData& OldCritDamage) const;
	UFUNCTION() void OnRep_Omnivamp(const FGameplayAttributeData& OldOmnivamp) const;
	UFUNCTION() void OnRep_SpellVamp(const FGameplayAttributeData& OldSpellVamp) const;
	UFUNCTION() void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const;
	UFUNCTION() void OnRep_AttackRange(const FGameplayAttributeData& OldAttackRange) const;
	UFUNCTION() void OnRep_AbilityHaste(const FGameplayAttributeData& OldAbilityHaste) const;
	UFUNCTION() void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	UFUNCTION() void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
	UFUNCTION() void OnRep_HealAndShieldPower(const FGameplayAttributeData& OldHealAndShieldPower) const;
	UFUNCTION() void OnRep_OnHitDamagePhys(const FGameplayAttributeData& OldOnHitDamagePhys) const;
	UFUNCTION() void OnRep_OnHitDamageMag(const FGameplayAttributeData& OldOnHitDamageMag) const;
	UFUNCTION() void OnRep_OnHitDamagePctPhys(const FGameplayAttributeData& OldOnHitDamagePctPhys) const;
	UFUNCTION() void OnRep_OnHitDamagePctMag(const FGameplayAttributeData& OldOnHitDamagePctMag) const;
	UFUNCTION() void OnRep_ProcCounter(const FGameplayAttributeData& OldProcCounter) const;
	UFUNCTION() void OnRep_Gold(const FGameplayAttributeData& OldGold) const;

	/* Vital OnReps */
	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION() void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION() void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;
	UFUNCTION() void OnRep_Sanity(const FGameplayAttributeData& OldSanity) const;
	UFUNCTION() void OnRep_Hunger(const FGameplayAttributeData& OldHunger) const;

	/* Resistance OnReps */
	UFUNCTION() void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const;
	UFUNCTION() void OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const;
	UFUNCTION() void OnRep_ArcaneResistance(const FGameplayAttributeData& OldArcaneResistance) const;
	UFUNCTION() void OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const;
	UFUNCTION() void OnRep_Tenacity(const FGameplayAttributeData& OldTenacity) const;

	
	private:
	
	void SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
