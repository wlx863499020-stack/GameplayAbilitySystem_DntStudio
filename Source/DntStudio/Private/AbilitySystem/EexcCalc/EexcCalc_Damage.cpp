// DntStudio

#include "AbilitySystem/EexcCalc/EexcCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "DntAbilityTypes.h"
#include "DntGameplayTags.h"
#include "AbilitySystem/DntAbilitySystemLibrary.h"
#include "AbilitySystem/DntAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"

struct DntDamageStatics
{
	/* --- LoL 核心防御与穿透 (Target & Source) --- */
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);               // 护甲 (Target)
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicResistance);     // 魔抗 (Target)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);    // 固定护穿 (Source)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenPercent);     // 百分比护穿 (Source)
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicPenetration);    // 固定法穿 (Source)
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicPenPercent);     // 百分比法穿 (Source)

	/* --- LoL 核心攻击缩放 (Source) --- */
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackDamage);        // 物理攻击力 (AD)
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbilityPower);        // 法术强度 (AP)

	/* --- LoL 战斗机制 (Source & Target) --- */
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritChance);          // 暴击率
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);   // 暴击伤害
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance); // 暴击抗性 (兰顿之兆逻辑)
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);         // 格挡率

	/* --- GAS 课程特有：三个百分比减伤参数 (Target) --- */
	/* 这里的逻辑：50.0 代表减免 50% 伤害 */
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);  // 物理硬减伤 (牛头R)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance);    // 魔法硬减伤 (牛头R)
	DECLARE_ATTRIBUTE_CAPTUREDEF(TrueResistance);      // 真实伤害硬减伤

	/* --- LoL 攻击特效 (Source) --- */
	DECLARE_ATTRIBUTE_CAPTUREDEF(OnHitDamagePhys);     // 普攻物理附伤 (多兰/智慧末刃)
	DECLARE_ATTRIBUTE_CAPTUREDEF(OnHitDamageMag);      // 普攻魔法附伤 (维鲁斯W/纳什)
	DECLARE_ATTRIBUTE_CAPTUREDEF(OnHitDamagePctPhys);  // 普攻物理百分比 (破败)
	DECLARE_ATTRIBUTE_CAPTUREDEF(OnHitDamagePctMag);   // 普攻魔法百分比 (百分比附伤)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ProcCounter);         // 计数器 (羊刀)
	
	DECLARE_ATTRIBUTE_CAPTUREDEF(LifeSteal);
	DECLARE_ATTRIBUTE_CAPTUREDEF(SpellVamp);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Omnivamp);

	/* --- 辅助计算 (Target) --- */
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxHealth);           // 用于计算最大生命值百分比伤害
	 

	DntDamageStatics()
	{
		const FDntGameplayTags& Tags = FDntGameplayTags::Get();

		// 定义捕捉逻辑 (捕捉谁, 来源, 是否快照)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, MagicResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, ArmorPenPercent, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, MagicPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, MagicPenPercent, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, AttackDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, AbilityPower, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, CritChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, CriticalHitDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, CriticalHitResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, BlockChance, Target, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, PhysicalResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, ArcaneResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, TrueResistance, Target, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, OnHitDamagePhys, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, OnHitDamageMag, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, OnHitDamagePctPhys, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, OnHitDamagePctMag, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, ProcCounter, Source, false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, LifeSteal, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, SpellVamp, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, Omnivamp, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UDntAttributeSet, MaxHealth, Target, false);
		
	}
};

static const DntDamageStatics& DamageStatics()
{
	static DntDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	// 注册 LoL 核心防御
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenPercentDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicPenPercentDef);

	// 注册 AD/AP 缩放
	RelevantAttributesToCapture.Add(DamageStatics().AttackDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().AbilityPowerDef);

	// 注册 暴击/格挡
	RelevantAttributesToCapture.Add(DamageStatics().CritChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);

	// 注册 三个百分比硬减伤
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArcaneResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().TrueResistanceDef);

	// 注册 On-Hit 系统
	RelevantAttributesToCapture.Add(DamageStatics().OnHitDamagePhysDef);
	RelevantAttributesToCapture.Add(DamageStatics().OnHitDamageMagDef);
	RelevantAttributesToCapture.Add(DamageStatics().OnHitDamagePctPhysDef);
	RelevantAttributesToCapture.Add(DamageStatics().OnHitDamagePctMagDef);
	RelevantAttributesToCapture.Add(DamageStatics().ProcCounterDef);

	// 辅助
	RelevantAttributesToCapture.Add(DamageStatics().MaxHealthDef);
}

void UExecCalc_Damage::DetermineDebuff(const FGameplayEffectCustomExecutionParameters& ExecutionParams, const FGameplayEffectSpec& Spec, FAggregatorEvaluateParameters EvaluateParameters, 
	const TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& InTagsToDefs) const
{
	const FDntGameplayTags& GameplayTags = FDntGameplayTags::Get();

	for (TTuple<FGameplayTag, FGameplayTag> Pair : GameplayTags.DamageTypesToDebuffs)
	{
		const FGameplayTag& DamageType = Pair.Key;
		const FGameplayTag& DebuffType = Pair.Value;
		const float TypeDamage = Spec.GetSetByCallerMagnitude(DamageType, false, -1.f);
		if (TypeDamage > -.5f) // .5 padding for floating point [im]precision
		{
			// Determine if there was a successful debuff
			const float SourceDebuffChance = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Chance, false, -1.f);

			float TargetDebuffResistance = 0.f;
			const FGameplayTag& ResistanceTag = GameplayTags.DamageTypesToResistances[DamageType];
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(InTagsToDefs[ResistanceTag],EvaluateParameters,	TargetDebuffResistance);
			TargetDebuffResistance = FMath::Max<float>(TargetDebuffResistance, 0.f);
			const float EffectiveDebuffChance = SourceDebuffChance * (100 - TargetDebuffResistance) / 100.f;
			const bool bDebuff = FMath::RandRange(1, 100) < EffectiveDebuffChance;
			if (bDebuff)
			{
				FGameplayEffectContextHandle ContextHandle = Spec.GetContext();

				UDntAbilitySystemLibrary::SetIsSuccessfulDebuff(ContextHandle, true);
				UDntAbilitySystemLibrary::SetDamageTypeTag(ContextHandle, DamageType); 
				const float DebuffDamage = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Damage, false, -1.f);
				const float DebuffDuration = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Duration, false,  -1.f);
				const float DebuffFrequency = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Frequency,  false,  -1.f);

				UDntAbilitySystemLibrary::SetDebuffDamage(ContextHandle, DebuffDamage);
				UDntAbilitySystemLibrary::SetDebuffDuration( ContextHandle, DebuffDuration);
				UDntAbilitySystemLibrary::SetDebuffFrequency( ContextHandle, DebuffFrequency);
			}
		}
	}
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	const FDntGameplayTags& Tags = FDntGameplayTags::Get();

	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Armor, DamageStatics().ArmorDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_BlockChance, DamageStatics().BlockChanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_ArmorPenetration, DamageStatics().ArmorPenetrationDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CritChance, DamageStatics().CritChanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitResistance, DamageStatics().CriticalHitResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitDamage, DamageStatics().CriticalHitDamageDef);

	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_ArcaneResistance, DamageStatics().ArcaneResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_PhysicalResistance, DamageStatics().PhysicalResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_TrueResistance, DamageStatics().TrueResistanceDef);
	
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	
	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	
	int32 SourcePlayerLevel = 1;
	if (SourceAvatar->Implements<UCombatInterface>())
	{
		SourcePlayerLevel = ICombatInterface::Execute_GetPlayerLevel(SourceAvatar);
	}

	int32 TargetPlayerLevel = 1;
	if (TargetAvatar->Implements<UCombatInterface>())
	{
		TargetPlayerLevel = ICombatInterface::Execute_GetPlayerLevel(TargetAvatar);
	}
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	//Debuff
	
	DetermineDebuff(ExecutionParams, Spec, EvaluateParameters, TagsToCaptureDefs);
	
	// ==============================================================
	// 1. 获取原始伤害 并 应用“硬减伤”（自创的三个百分比减伤属性）
	// 这里处理：PhysicalResistance, ArcaneResistance, TrueResistance
	// ==============================================================
	float TotalPhysicalDamage = 0.f; 
	float TotalMagicalDamage = 0.f;  
	float TotalTrueDamage = 0.f;     

	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : Tags.DamageTypesToResistances)
	{
		const FGameplayTag DamageTypeTag = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;
		
		checkf(TagsToCaptureDefs.Contains(ResistanceTag), TEXT("TagsToCaptureDefs does not contain [%s]"), *ResistanceTag.ToString());
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = TagsToCaptureDefs[ResistanceTag];
		
		float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key, false);
		if (DamageTypeValue <= 0.f) continue;
		
		// 捕捉自创的“硬减伤”百分比 (牛头大招逻辑)
		float CustomResistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluateParameters, CustomResistance);
		CustomResistance = FMath::Clamp(CustomResistance, 0.f, 99.f); 
		
		// 第一次减伤：直接百分比扣除 (例如 CustomResistance = 50，伤害减半)
		DamageTypeValue *= (100.f - CustomResistance) / 100.f;
		
		// 按伤害类型归类，准备后续的 LoL 防御计算
		if (DamageTypeTag.MatchesTagExact(Tags.Damage_Physical)) TotalPhysicalDamage += DamageTypeValue;
		else if (DamageTypeTag.MatchesTagExact(Tags.Damage_Arcane)) TotalMagicalDamage += DamageTypeValue;
		else if (DamageTypeTag.MatchesTagExact(Tags.Damage_True)) TotalTrueDamage += DamageTypeValue;
	}

	// ==============================================================
	// 2. 暴击计算 (League of Legends Multiplicative Style)
	// ==============================================================
	float SourceCritChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritChanceDef, EvaluateParameters, SourceCritChance);

	float SourceCritDamageBonus = 0.f; // 装备提供的额外暴击伤害 (如无尽)
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef, EvaluateParameters, SourceCritDamageBonus);
	
	float TargetCritReduction = 0.f; // 目标的暴击抗性 (如兰顿)
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef, EvaluateParameters, TargetCritReduction);

	const bool bCrit = FMath::RandRange(1, 100) < SourceCritChance;
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	UDntAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCrit);
	
	if (bCrit)
	{
		// LoL 公式：基础暴击伤害是 175% 或 200%。这里我们假设基础是 2.0倍
		float IE_Multiplier = (SourceCritDamageBonus / 100.f);     
		float Randuin_Reduction = (TargetCritReduction / 100.f); 

		float FinalCritMultiplier = 2.0f + IE_Multiplier - Randuin_Reduction;
		FinalCritMultiplier = FMath::Max(FinalCritMultiplier, 1.0f); // 至少造成1倍伤害

		// 暴击应用在物理和魔法上
		TotalPhysicalDamage *= FinalCritMultiplier;
		TotalMagicalDamage *= FinalCritMultiplier;
	}

	// ==============================================================
	// 3. 格挡计算
	// ==============================================================
	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluateParameters, TargetBlockChance);
	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;
	UDntAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);

	if (bBlocked)
	{
		TotalPhysicalDamage *= 0.7f; // 格挡减免 30%
		TotalMagicalDamage *= 0.7f;
	}

	// ==============================================================
	// 4. 英雄联盟防御曲线计算 (核心：Armor/MR 与 穿透)
	// 逻辑：先算百分比穿透，再算固定穿透
	// ==============================================================
    
    // 获取等级系数 (用于 100 法则基数)
	const UCharacterClassInfo* CharacterClassInfo = UDntAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	const float ArmorPenetrationCoefficient = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString())->Eval(SourcePlayerLevel);
	const float EffectiveArmorCoefficient = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString())->Eval(TargetPlayerLevel);

    // --- A. 物理穿透与护甲结算 ---
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluateParameters, TargetArmor);
	float SourceArmorPen = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluateParameters, SourceArmorPen);
	float SourceArmorPenPct = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenPercentDef, EvaluateParameters, SourceArmorPenPct);

	// LoL 穿透顺序：有效护甲 = (护甲 * (1 - 百分比穿透)) - 固定穿透
	float EffArmor = (TargetArmor * (100.f - SourceArmorPenPct) / 100.f) - (SourceArmorPen * ArmorPenetrationCoefficient);
	EffArmor = FMath::Max(EffArmor, 0.f);
	TotalPhysicalDamage *= (EffectiveArmorCoefficient / (EffectiveArmorCoefficient + EffArmor));

    // --- B. 魔法穿透与魔抗结算 ---
    float TargetMR = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicResistanceDef, EvaluateParameters, TargetMR);
    float SourceMagPen = 0.f; 
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicPenetrationDef, EvaluateParameters, SourceMagPen);
    float SourceMagPenPct = 0.f; 
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicPenPercentDef, EvaluateParameters, SourceMagPenPct);

    // LoL 穿透顺序：有效魔抗 = (魔抗 * (1 - 百分比法穿)) - 固定法穿
    float EffMR = (TargetMR * (100.f - SourceMagPenPct) / 100.f) - SourceMagPen;
    EffMR = FMath::Max(EffMR, 0.f);
    TotalMagicalDamage *= (EffectiveArmorCoefficient / (EffectiveArmorCoefficient + EffMR));

	// ==============================================================
	// 5. 最终数值合并 (物理 + 魔法 + 真实伤害)
	// ==============================================================
	float FinalDamage = TotalPhysicalDamage + TotalMagicalDamage + TotalTrueDamage;
	 
	// ==============================================================
	// 6. 输出到 IncomingDamage
	// ==============================================================
	
	
	const FGameplayModifierEvaluatedData EvaluatedData(UDntAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, FinalDamage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	UE_LOG(LogTemp, Warning, TEXT("Final Calculated Damage: %f"), FinalDamage);
}
