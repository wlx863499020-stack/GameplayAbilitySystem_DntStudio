// DntStudio


#include "AbilitySystem/DntAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "DntGameplayTags.h"
#include "AbilitySystem/DntAbilitySystemLibrary.h"
#include "DntStudio/DntLogChannals.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DntPlayerController.h"

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
	
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_PhysicalResistance, GetPhysicalResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_ArcaneResistance, GetMagicResistanceAttribute);
	
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
 * Primary Attributes (核心五维 + 精神力)  Strength, Intelligence, Resilience, Vigor, Luck, Spirit
 */
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Strength, COND_None, REPNOTIFY_Always);        // 力量
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);    // 智力
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Resilience, COND_None, REPNOTIFY_Always);      // 韧性
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Vigor, COND_None, REPNOTIFY_Always);           // 活力
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, ManaVigor, COND_None, REPNOTIFY_Always);       // 法力活力
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Luck, COND_None, REPNOTIFY_Always);            // 幸运
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Spirit, COND_None, REPNOTIFY_Always);          // 精神

/*
 *Secondary Attributes (衍生战斗属性)AttackDamage, AbilityPower, Armor, MagicResistance,
 *ArmorPenetration, ArmorPenPercent, MagicPenetration, MagicPenPercent,CritChance, 
 *MagicalCritChance, CriticalHitDamage, Omnivamp, SpellVamp,AttackSpeed, AttackRange, AbilityHaste, Gold
 */
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);        // 最大生命值
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);          // 最大法力值
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);       // 最大体力值
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, MaxSanity, COND_None, REPNOTIFY_Always);        // 最大理智值
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, MaxHunger, COND_None, REPNOTIFY_Always);        // 最大饥饿值
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, AttackDamage, COND_None, REPNOTIFY_Always);     // 攻击力
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, AbilityPower, COND_None, REPNOTIFY_Always);     // 法术强度
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Armor, COND_None, REPNOTIFY_Always);            // 护甲
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, MagicResistance, COND_None, REPNOTIFY_Always);  // 魔法抗性
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always); // 护甲穿透
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, ArmorPenPercent, COND_None, REPNOTIFY_Always);  // 百分比护甲穿透
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, MagicPenetration, COND_None, REPNOTIFY_Always); // 法术穿透
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, MagicPenPercent, COND_None, REPNOTIFY_Always);  // 百分比法术穿透
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, CritChance, COND_None, REPNOTIFY_Always);       // 暴击率
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);      // 格挡率
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, MagicalCritChance, COND_None, REPNOTIFY_Always); // 法术暴击率
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always); // 暴击伤害
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always); // 暴击抗性
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Omnivamp, COND_None, REPNOTIFY_Always);           // 全能吸血
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, LifeSteal, COND_None, REPNOTIFY_Always);          // 物理吸血
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, SpellVamp, COND_None, REPNOTIFY_Always);          // 法术吸血
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);        // 攻击速度
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, AttackRange, COND_None, REPNOTIFY_Always);        // 攻击距离
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, AbilityHaste, COND_None, REPNOTIFY_Always);       // 技能急速
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always); // 生命回复
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);   // 法力回复
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, HealAndShieldPower, COND_None, REPNOTIFY_Always); // 治疗护盾强度
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, OnHitDamagePhys, COND_None, REPNOTIFY_Always);    // 攻击特效物理附加伤害
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, OnHitDamageMag, COND_None, REPNOTIFY_Always);     // 攻击特效魔法附加伤害
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, OnHitDamagePctPhys, COND_None, REPNOTIFY_Always); // 攻击特效百分比物理伤害
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, OnHitDamagePctMag, COND_None, REPNOTIFY_Always);  // 攻击特效百分比魔法伤害
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, ProcCounter, COND_None, REPNOTIFY_Always);        // 触发计数器
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Gold, COND_None, REPNOTIFY_Always);               // 金币
	DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Tenacity, COND_None, REPNOTIFY_Always);       // 韧性

/*
 * Vital Attributes (实时状态资源)Health, Mana, Stamina, Sanity, Hunger
 */
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Health, COND_None, REPNOTIFY_Always);           // 生命值
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Mana, COND_None, REPNOTIFY_Always);             // 法力值
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Stamina, COND_None, REPNOTIFY_Always);          // 体力值
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Sanity, COND_None, REPNOTIFY_Always);           // 理智值
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, Hunger, COND_None, REPNOTIFY_Always);           // 饥饿值

/*
 * Resistance Attributes (抗性属性)TrueResistance, MagicResistance, PhysicalResistance, Tenacity
 */
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, TrueResistance, COND_None, REPNOTIFY_Always);     // 真实伤害抗性
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, MagicResistance, COND_None, REPNOTIFY_Always);    // 魔法抗性
DOREPLIFETIME_CONDITION_NOTIFY(UDntAttributeSet, PhysicalResistance, COND_None, REPNOTIFY_Always); // 物理抗性
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

	// 1. 【死亡检查】如果目标已经死亡，不再处理后续任何伤害或经验结算（防止鞭尸发经验）
	if (Props.TargetCharacter->Implements<UCombatInterface>() && ICombatInterface::Execute_IsDead(Props.TargetCharacter))
	{
		return;
	}
	
    // 2. 【基础属性 Clamp】确保所有 Vital 属性在变动后不越界
    if (Data.EvaluatedData.Attribute == GetHealthAttribute())   SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
    if (Data.EvaluatedData.Attribute == GetManaAttribute())     SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
    if (Data.EvaluatedData.Attribute == GetStaminaAttribute())  SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
    if (Data.EvaluatedData.Attribute == GetSanityAttribute())   SetSanity(FMath::Clamp(GetSanity(), 0.f, GetMaxSanity()));
    if (Data.EvaluatedData.Attribute == GetHungerAttribute())   SetHunger(FMath::Clamp(GetHunger(), 0.f, GetMaxHunger()));

	// 3. 【核心结算】处理伤害管道 (IncomingDamage)
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();

		if (LocalIncomingDamage > 0.f)
		{
			// --- A. 触发 UI 飘字 ---
			// 必须在 SetIncomingDamage(0.f) 之前调用，因为 Handle 内部会 GetIncomingDamage()
			HandleIncomingDamage(Props);

			// --- B. 执行扣血逻辑 ---
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

			// --- C. 清空管道数值 ---
			SetIncomingDamage(0.f);

			// --- D. 死亡与后续逻辑 ---
			const bool bFatalHit = NewHealth <= 0.f;
			if (bFatalHit)
			{
				ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetCharacter);
				if (CombatInterface)
				{
					// 传递死亡冲量，实现英雄联盟/ACT中的击飞死亡效果
					CombatInterface->Die(UDntAbilitySystemLibrary::GetDeathImpulse(Props.EffectContextHandle));
				}
			}
			else
			{
				// 如果目标没死，尝试触发 Debuff 特效（产生持续伤害的 GE）
				if (UDntAbilitySystemLibrary::IsSuccessfulDebuff(Props.EffectContextHandle))
				{
					Debuff(Props); 
				}
			}
		}
	}

	// 4. 【经验值结算】
	if (Data.EvaluatedData.Attribute == GetIncomingXPAttribute())
	{
		HandleIncomingXP(Props);
	}

	// 5. 【金钱结算】处理你自定义的英雄联盟金币获取
	if (Data.EvaluatedData.Attribute == GetIncomingGoldAttribute())
	{
		const float LocalIncomingGold = GetIncomingGold();
		// 清空管道
		SetIncomingGold(0.f);
		
		if (LocalIncomingGold > 0.f)
		{
			const float CurrentGold = GetGold();
			SetGold(CurrentGold + LocalIncomingGold);
			
			// 此处可以添加一个 UE_LOG 或发送一个 GameplayEvent 来通知 UI 播放“金币增加”动画
		}
	}
}

void UDntAttributeSet::HandleIncomingDamage(const FEffectProperties& Props)
{
	const float LocalIncomingDamage = GetIncomingDamage();
	SetIncomingDamage(0.f);
	if(LocalIncomingDamage > 0.f)
	{
		const float NewHealth = GetHealth() - LocalIncomingDamage;
		SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));
			
		const bool bFatal = NewHealth <= 0.f;
		if (bFatal)
		{
			ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor);
			if (CombatInterface)
			{
				FVector Impulse = UDntAbilitySystemLibrary::GetDeathImpulse(Props.EffectContextHandle);
				CombatInterface->Die(UDntAbilitySystemLibrary::GetDeathImpulse(Props.EffectContextHandle));
			}
			SendXPEvent(Props);
		}
		else
		{
			FGameplayTagContainer TagContainer;
			TagContainer.AddTag(FDntGameplayTags::Get().Effect_HitReact);
			Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
			
			const FVector& KnockbackForce = UDntAbilitySystemLibrary::GetKnockbackForce(Props.EffectContextHandle);
			if (!KnockbackForce.IsNearlyZero(1.f))
			{
				Props.TargetCharacter->LaunchCharacter(KnockbackForce, true, true);
			}
		}
			
			
		const bool bBlock = UDntAbilitySystemLibrary::IsBlockedHit(Props.EffectContextHandle);
		const bool bCriticalHit = UDntAbilitySystemLibrary::IsCriticalHit(Props.EffectContextHandle);
		ShowFloatingText(Props, LocalIncomingDamage,bBlock,bCriticalHit);	
		if (UDntAbilitySystemLibrary::IsSuccessfulDebuff(Props.EffectContextHandle))
		{
			Debuff(Props);
		}
	}
}

void UDntAttributeSet::Debuff(const FEffectProperties& Props)
{
	const FDntGameplayTags& GameplayTags = FDntGameplayTags::Get();
	FGameplayEffectContextHandle EffectContext = Props.SourceASC->MakeEffectContext();
	EffectContext.AddSourceObject(Props.SourceAvatarActor);

	const FGameplayTag DamageType = UDntAbilitySystemLibrary::GetDamageTypeTag(Props.EffectContextHandle);
	const float DebuffDamage = UDntAbilitySystemLibrary::GetDebuffDamage(Props.EffectContextHandle);
	const float DebuffDuration = UDntAbilitySystemLibrary::GetDebuffDuration(Props.EffectContextHandle);
	const float DebuffFrequency = UDntAbilitySystemLibrary::GetDebuffFrequency(Props.EffectContextHandle);

	FString DebuffName = FString::Printf(TEXT("DynamicDebuff_%s"), *DamageType.ToString());
	UGameplayEffect* Effect = NewObject<UGameplayEffect>(GetTransientPackage(), FName(DebuffName));

	Effect->DurationPolicy = EGameplayEffectDurationType::HasDuration;
	Effect->Period = DebuffFrequency;
	Effect->DurationMagnitude = FScalableFloat(DebuffDuration);

	Effect->InheritableOwnedTagsContainer.AddTag(GameplayTags.DamageTypesToDebuffs[DamageType]);

	Effect->StackingType = EGameplayEffectStackingType::AggregateBySource;
	Effect->StackLimitCount = 1;
	
	const int32 Index = Effect->Modifiers.Num();
	Effect->Modifiers.Add(FGameplayModifierInfo());
	FGameplayModifierInfo& ModifierInfo = Effect->Modifiers[Index];

	ModifierInfo.ModifierMagnitude = FScalableFloat(DebuffDamage);
	ModifierInfo.ModifierOp = EGameplayModOp::Additive;
	ModifierInfo.Attribute = UDntAttributeSet::GetIncomingDamageAttribute();

	if (FGameplayEffectSpec* MutableSpec = new FGameplayEffectSpec(Effect, EffectContext, 1.f))
	{
		FDntGameplayEffectContext* DntContext = static_cast<FDntGameplayEffectContext*>(MutableSpec->GetContext().Get());
		DntContext->SetDamageTypeTag(DamageType); 

		Props.TargetASC->ApplyGameplayEffectSpecToSelf(*MutableSpec);
	}
}

void UDntAttributeSet::HandleIncomingXP(const FEffectProperties& Props)
{
	const float LocalIncomingXP = GetIncomingXP();
	SetIncomingXP(0.f);
		
	//TODO: See if we should level up
		
	// Source Character is the owner, since GA_ListenForEvents applies GE_EventBasedEffect, adding to IncomingXP
	if (Props.SourceCharacter->Implements<UPlayerInterface>() && Props.SourceCharacter->Implements<UCombatInterface>())
	{
		const int32 CurrentLevel = ICombatInterface::Execute_GetPlayerLevel(Props.SourceCharacter);
		const int32 CurrentXP = IPlayerInterface::Execute_GetXP(Props.SourceCharacter);

		const int32 NewLevel = IPlayerInterface::Execute_FindLevelForXP(Props.SourceCharacter, CurrentXP + LocalIncomingXP);
		const int32 NumLevelUps = NewLevel - CurrentLevel;
		if (NumLevelUps > 0)
		{
			const int32 AttributePointsReward = IPlayerInterface::Execute_GetAttributePointsReward(Props.SourceCharacter, CurrentLevel);
			const int32 SpellPointsReward = IPlayerInterface::Execute_GetSpellPointsReward(Props.SourceCharacter, CurrentLevel);

			IPlayerInterface::Execute_AddToPlayerLevel(Props.SourceCharacter, NumLevelUps);
			IPlayerInterface::Execute_AddToAttributePoints(Props.SourceCharacter, AttributePointsReward);
			IPlayerInterface::Execute_AddToSpellPoints(Props.SourceCharacter, SpellPointsReward);

			bTopOffHealth = true;
			bTopOffMana = true;

			IPlayerInterface::Execute_LevelUp(Props.SourceCharacter);
		}

		IPlayerInterface::Execute_AddToXP(Props.SourceCharacter, LocalIncomingXP);
	}
}



void UDntAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	if (Attribute == GetMaxHealthAttribute() && bTopOffHealth)
	{
		float HealthDelta = NewValue - OldValue;
		SetHealth(GetHealth() + HealthDelta);
		bTopOffHealth = false;
	}

	if (Attribute == GetMaxManaAttribute() && bTopOffMana)
	{
		float ManaDelta = NewValue - OldValue;
		SetMana(GetMana() + ManaDelta);
		bTopOffMana = false;
	}
	
}

void UDntAttributeSet::ShowFloatingText(const FEffectProperties& Props, float Damage,bool bBlockedHit, bool bCriticalHit) const
{
	if (Props.SourceCharacter != Props.TargetCharacter)
	{
		if(ADntPlayerController* PC = Cast<ADntPlayerController>(Props.SourceCharacter->Controller))
		{
			PC->ShowDamageNumber(Damage,Props.TargetCharacter, bBlockedHit, bCriticalHit);
			return;
		}
		
		if(ADntPlayerController* PC = Cast<ADntPlayerController>(Props.TargetCharacter->Controller))
		{
			PC->ShowDamageNumber(Damage,Props.TargetCharacter, bBlockedHit, bCriticalHit);
		}
	}
}

void UDntAttributeSet::SendXPEvent(const FEffectProperties& Props)
{
	if (Props.TargetCharacter->Implements<UCombatInterface>())
	{
		const int32 TargetLevel = ICombatInterface::Execute_GetPlayerLevel(Props.TargetCharacter);
		const ECharacterClass TargetClass = ICombatInterface::Execute_GetCharacterClass(Props.TargetCharacter);
		const int32 XPReward = UDntAbilitySystemLibrary::GetXPRewardForClassAndLevel(Props.TargetCharacter, TargetClass, TargetLevel);

		const FDntGameplayTags& GameplayTags = FDntGameplayTags::Get();
		FGameplayEventData Payload;
		Payload.EventTag = GameplayTags.Attributes_Meta_IncomingXP;
		Payload.EventMagnitude = XPReward;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Props.SourceCharacter, GameplayTags.Attributes_Meta_IncomingXP, Payload);
	}
}

/*
 * 一、 Primary Attributes (基础属性)
 */
void UDntAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Strength, OldStrength); }                // 力量

void UDntAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Intelligence, OldIntelligence); }        // 智力

void UDntAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Resilience, OldResilience); }            // 韧性

void UDntAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Vigor, OldVigor); }                       // 活力

void UDntAttributeSet::OnRep_ManaVigor(const FGameplayAttributeData& OldManaVigor) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, ManaVigor, OldManaVigor); }               // 法力活力

void UDntAttributeSet::OnRep_Luck(const FGameplayAttributeData& OldLuck) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Luck, OldLuck); }                         // 幸运

void UDntAttributeSet::OnRep_Spirit(const FGameplayAttributeData& OldSpirit) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Spirit, OldSpirit); }                     // 精神

/*
 * 二、 Secondary Attributes (衍生战斗属性)
 */
void UDntAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, MaxHealth, OldMaxHealth); }               // 最大生命值

void UDntAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, MaxMana, OldMaxMana); }                   // 最大法力值

void UDntAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, MaxStamina, OldMaxStamina); }              // 最大体力值

void UDntAttributeSet::OnRep_MaxSanity(const FGameplayAttributeData& OldMaxSanity) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, MaxSanity, OldMaxSanity); }              // 最大理智值

void UDntAttributeSet::OnRep_MaxHunger(const FGameplayAttributeData& OldMaxHunger) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, MaxHunger, OldMaxHunger); }              // 最大饥饿值

void UDntAttributeSet::OnRep_AttackDamage(const FGameplayAttributeData& OldAttackDamage) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, AttackDamage, OldAttackDamage); }         // 攻击力

void UDntAttributeSet::OnRep_AbilityPower(const FGameplayAttributeData& OldAbilityPower) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, AbilityPower, OldAbilityPower); }         // 法术强度

void UDntAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Armor, OldArmor); }                       // 护甲

void UDntAttributeSet::OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, MagicResistance, OldMagicResistance); }   // 魔法抗性

void UDntAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, ArmorPenetration, OldArmorPenetration); } // 护甲穿透

void UDntAttributeSet::OnRep_ArmorPenPercent(const FGameplayAttributeData& OldArmorPenPercent) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, ArmorPenPercent, OldArmorPenPercent); }   // 百分比护甲穿透

void UDntAttributeSet::OnRep_MagicPenetration(const FGameplayAttributeData& OldMagicPenetration) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, MagicPenetration, OldMagicPenetration); } // 法术穿透

void UDntAttributeSet::OnRep_MagicPenPercent(const FGameplayAttributeData& OldMagicPenPercent) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, MagicPenPercent, OldMagicPenPercent); }   // 百分比法术穿透

void UDntAttributeSet::OnRep_CritChance(const FGameplayAttributeData& OldCritChance) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, CritChance, OldCritChance); }               // 暴击率

void UDntAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, BlockChance, OldBlockChance); }            // 格挡率

void UDntAttributeSet::OnRep_MagicalCritChance(const FGameplayAttributeData& OldMagicalCritChance) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, MagicalCritChance, OldMagicalCritChance); } // 法术暴击率

void UDntAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, CriticalHitDamage, OldCriticalHitDamage); } // 暴击伤害

void UDntAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, CriticalHitResistance, OldCriticalHitResistance); } // 暴击抗性

void UDntAttributeSet::OnRep_LifeSteal(const FGameplayAttributeData& OldLifeSteal) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, LifeSteal, OldLifeSteal); }                // 物理吸血

void UDntAttributeSet::OnRep_Omnivamp(const FGameplayAttributeData& OldOmnivamp) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Omnivamp, OldOmnivamp); }                   // 全能吸血

void UDntAttributeSet::OnRep_SpellVamp(const FGameplayAttributeData& OldSpellVamp) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, SpellVamp, OldSpellVamp); }                 // 法术吸血

void UDntAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, AttackSpeed, OldAttackSpeed); }             // 攻击速度

void UDntAttributeSet::OnRep_AttackRange(const FGameplayAttributeData& OldAttackRange) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, AttackRange, OldAttackRange); }             // 攻击距离

void UDntAttributeSet::OnRep_AbilityHaste(const FGameplayAttributeData& OldAbilityHaste) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, AbilityHaste, OldAbilityHaste); }           // 技能急速

void UDntAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, HealthRegeneration, OldHealthRegeneration); } // 生命回复

void UDntAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, ManaRegeneration, OldManaRegeneration); }   // 法力回复

void UDntAttributeSet::OnRep_HealAndShieldPower(const FGameplayAttributeData& OldHealAndShieldPower) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, HealAndShieldPower, OldHealAndShieldPower); } // 治疗护盾强度

void UDntAttributeSet::OnRep_Gold(const FGameplayAttributeData& OldGold) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Gold, OldGold); }                           // 金币

void UDntAttributeSet::OnRep_OnHitDamagePhys(const FGameplayAttributeData& OldOnHitDamagePhys) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, OnHitDamagePhys, OldOnHitDamagePhys); }    // 攻击特效物理附加伤害

void UDntAttributeSet::OnRep_OnHitDamageMag(const FGameplayAttributeData& OldOnHitDamageMag) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, OnHitDamageMag, OldOnHitDamageMag); }       // 攻击特效魔法附加伤害

void UDntAttributeSet::OnRep_OnHitDamagePctPhys(const FGameplayAttributeData& OldOnHitDamagePctPhys) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, OnHitDamagePctPhys, OldOnHitDamagePctPhys); } // 攻击特效百分比物理伤害

void UDntAttributeSet::OnRep_OnHitDamagePctMag(const FGameplayAttributeData& OldOnHitDamagePctMag) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, OnHitDamagePctMag, OldOnHitDamagePctMag); } // 攻击特效百分比魔法伤害

void UDntAttributeSet::OnRep_ProcCounter(const FGameplayAttributeData& OldProcCounter) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, ProcCounter, OldProcCounter); }             // 触发计数器

void UDntAttributeSet::OnRep_Tenacity(const FGameplayAttributeData& OldTenacity) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Tenacity, OldTenacity); }                   // 韧性

/*
 * 三、 Vital Attributes (实时状态资源)
 */
void UDntAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Health, OldHealth); }                       // 生命值

void UDntAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Mana, OldMana); }                           // 法力值

void UDntAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Stamina, OldStamina); }                     // 体力值

void UDntAttributeSet::OnRep_Sanity(const FGameplayAttributeData& OldSanity) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Sanity, OldSanity); }                       // 理智值

void UDntAttributeSet::OnRep_Hunger(const FGameplayAttributeData& OldHunger) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, Hunger, OldHunger); }                       // 饥饿值

/*
 * 四、 Resistance Attributes (抗性与韧性)
 */
void UDntAttributeSet::OnRep_TrueResistance(const FGameplayAttributeData& OldTrueResistance) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, TrueResistance, OldTrueResistance); }       // 真实伤害抗性

void UDntAttributeSet::OnRep_ArcaneResistance(const FGameplayAttributeData& OldArcaneResistance) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, ArcaneResistance, OldArcaneResistance); }   // 奥术抗性

void UDntAttributeSet::OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const
{ GAMEPLAYATTRIBUTE_REPNOTIFY(UDntAttributeSet, PhysicalResistance, OldPhysicalResistance); } // 物理抗性





