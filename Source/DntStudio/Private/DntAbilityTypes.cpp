// DntStudio

#include "DntAbilityTypes.h"

bool FDntGameplayEffectContext::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	// 使用 uint64 以支持超过 32 位的掩码偏移 (当前最高位偏移为 44)
	uint64 RepBits = 0;

	// =========================================================
	// 1. 【打包掩码】(服务器端执行：根据变量状态设置对应的位)
	// =========================================================
	if (Ar.IsSaving())
	{
		// --- 引擎原生 & 核心上下文 (位 0-6) ---
		if (bReplicateInstigator && Instigator.IsValid())      { RepBits |= 1ULL << 0; }   // 0. 发起者
		if (bReplicateEffectCauser && EffectCauser.IsValid())  { RepBits |= 1ULL << 1; }   // 1. 效果来源
		if (AbilityCDO.IsValid())                              { RepBits |= 1ULL << 2; }   // 2. 技能原型
		if (bReplicateSourceObject && SourceObject.IsValid())  { RepBits |= 1ULL << 3; }   // 3. 原始对象
		if (Actors.Num() > 0)                                  { RepBits |= 1ULL << 4; }   // 4. 涉及角色组
		if (HitResult.IsValid())                               { RepBits |= 1ULL << 5; }   // 5. 命中结果
		if (bHasWorldOrigin)                                   { RepBits |= 1ULL << 6; }   // 6. 世界原点

		// --- 核心判定 (位 7-11) ---
		if (bIsBlockedHit)                                     { RepBits |= 1ULL << 7; }   // 7. 是否格挡
		if (bIsCriticalHit)                                    { RepBits |= 1ULL << 8; }   // 8. 是否暴击
		if (bIsDodgedHit)                                      { RepBits |= 1ULL << 9; }   // 9. 是否闪避
		if (bIsInvulnerableHit)                                { RepBits |= 1ULL << 10; }  // 10.是否无敌
		if (bIsShieldBroken)                                   { RepBits |= 1ULL << 11; }  // 11.是否破盾

		// --- Debuff 系统状态 (位 12-15) ---
		if (bIsSuccessfulDebuff)                               { RepBits |= 1ULL << 12; }  // 12.Debuff成功
		if (DebuffDamage > 0.f)                                { RepBits |= 1ULL << 13; }  // 13.Debuff伤害
		if (DebuffDuration > 0.f)                              { RepBits |= 1ULL << 14; }  // 14.Debuff时长
		if (DebuffFrequency > 0.f)                             { RepBits |= 1ULL << 15; }  // 15.Debuff频率

		// --- 伤害来源判定 (位 16-21) ---
		if (bIsBasicAttack)                                    { RepBits |= 1ULL << 16; }  // 16.是否普攻
		if (bIsAbilityDamage)                                  { RepBits |= 1ULL << 17; }  // 17.是否技能
		if (bIsPeriodicDamage)                                 { RepBits |= 1ULL << 18; }  // 18.是否DoT
		if (bIsAoEDamage)                                      { RepBits |= 1ULL << 19; }  // 19.是否AOE
		if (bIsPetDamage)                                      { RepBits |= 1ULL << 20; }  // 20.是否宠物伤
		if (bIsReflectedDamage)                                { RepBits |= 1ULL << 21; }  // 21.是否反弹伤

		// --- 特殊战斗事件 (位 22-24) ---
		if (bIsExecuteHit)                                     { RepBits |= 1ULL << 22; }  // 22.是否处决
		if (bHasLifesteal)                                     { RepBits |= 1ULL << 23; }  // 23.是否吸血
		if (bIsInterruptHit)                                   { RepBits |= 1ULL << 24; }  // 24.是否打断

		// --- 治疗与辅助空间 (位 25-28) ---
		if (bIsHeal)                                           { RepBits |= 1ULL << 25; }  // 25.是否治疗
		if (bIsShieldApplication)                              { RepBits |= 1ULL << 26; }  // 26.是否套盾
		if (bIsBackstab)                                       { RepBits |= 1ULL << 27; }  // 27.是否背刺
		if (bIsStealthHit)                                     { RepBits |= 1ULL << 28; }  // 28.是否隐身攻击

		// --- 环境与致死逻辑 (位 29-33) ---
		if (bIsTurretDamage)                                   { RepBits |= 1ULL << 29; }  // 29.是否塔伤
		if (bIsFountainDamage)                                 { RepBits |= 1ULL << 30; }  // 30.是否泉水伤
		if (bBypassesShields)                                  { RepBits |= 1ULL << 31; }  // 31.是否穿盾
		if (bIsFatalHit)                                       { RepBits |= 1ULL << 32; }  // 32.是否致死
		if (bIsNonLethal)                                      { RepBits |= 1ULL << 33; }  // 33.是否锁血

		// --- 扩展数值与表现 (位 34-42) ---
		if (DamageType != EDntDamageType::None)               { RepBits |= 1ULL << 34; }  // 34.LoL枚举
		if (DamageTypeTag.IsValid())                          { RepBits |= 1ULL << 35; }  // 35.元素标签
		if (TypeMultiplier != 1.0f)                           { RepBits |= 1ULL << 36; }  // 36.克制倍率
		if (!DeathImpulse.IsZero())                           { RepBits |= 1ULL << 37; }  // 37.死亡冲量
		if (!KnockbackForce.IsZero())                         { RepBits |= 1ULL << 38; }  // 38.击退力
		if (bIsRadialDamage)                                   { RepBits |= 1ULL << 39; }  // 39.是否径向
		if (RadialDamageInnerRadius > 0.f)                    { RepBits |= 1ULL << 40; }  // 40.径向内径
		if (RadialDamageOuterRadius > 0.f)                    { RepBits |= 1ULL << 41; }  // 41.径向外径
		if (!RadialDamageOrigin.IsZero())                     { RepBits |= 1ULL << 42; }  // 42.径向原点

		// --- Noita 零件与羊刀判定 (位 43-44) ---
		if (bIsPhantomHit)                                     { RepBits |= 1ULL << 43; }  // 43.羊刀幻影
		if (AppliedSpellParts.Num() > 0)                       { RepBits |= 1ULL << 44; }  // 44.Noita零件包
	}

	// =========================================================
	// 2. 【同步掩码】(传输共 45 位状态)
	// =========================================================
	Ar.SerializeBits(&RepBits, 45);

	// =========================================================
	// 3. 【执行序列化】(按位读写具体数值)
	// =========================================================

	// 基础对象读写
	if (RepBits & (1ULL << 0)) { Ar << Instigator; }                                       // 发起者
	if (RepBits & (1ULL << 1)) { Ar << EffectCauser; }                                     // 效果源
	if (RepBits & (1ULL << 2)) { Ar << AbilityCDO; }                                       // 技能原型
	if (RepBits & (1ULL << 3)) { Ar << SourceObject; }                                     // 原始对象
	if (RepBits & (1ULL << 4)) { SafeNetSerializeTArray_Default<31>(Ar, Actors); }          // 角色组
	if (RepBits & (1ULL << 5))                                                              // 命中结果
	{
		if (Ar.IsLoading()) { if (!HitResult.IsValid()) HitResult = TSharedPtr<FHitResult>(new FHitResult()); }
		HitResult->NetSerialize(Ar, Map, bOutSuccess);
	}
	if (RepBits & (1ULL << 6)) { Ar << WorldOrigin; bHasWorldOrigin = true; }              // 世界原点

	// 客户端数据解压 (7-33, 39, 43位)
	if (Ar.IsLoading())
	{
		bIsBlockedHit          = (RepBits & (1ULL << 7))  != 0;                            // 解包格挡
		bIsCriticalHit         = (RepBits & (1ULL << 8))  != 0;                            // 解包暴击
		bIsDodgedHit           = (RepBits & (1ULL << 9))  != 0;                            // 解包闪避
		bIsInvulnerableHit     = (RepBits & (1ULL << 10)) != 0;                           // 解包无敌
		bIsShieldBroken        = (RepBits & (1ULL << 11)) != 0;                           // 解包破盾
		bIsSuccessfulDebuff    = (RepBits & (1ULL << 12)) != 0;                           // 解包Debuff成功
		bIsBasicAttack         = (RepBits & (1ULL << 16)) != 0;                           // 解包普攻判定
		bIsAbilityDamage       = (RepBits & (1ULL << 17)) != 0;                           // 解包技能判定
		bIsPeriodicDamage      = (RepBits & (1ULL << 18)) != 0;                           // 解包DoT判定
		bIsAoEDamage           = (RepBits & (1ULL << 19)) != 0;                           // 解包AOE判定
		bIsPetDamage           = (RepBits & (1ULL << 20)) != 0;                           // 解包宠物判定
		bIsReflectedDamage     = (RepBits & (1ULL << 21)) != 0;                           // 解包反弹判定
		bIsExecuteHit          = (RepBits & (1ULL << 22)) != 0;                           // 解包处决判定
		bHasLifesteal          = (RepBits & (1ULL << 23)) != 0;                           // 解包吸血判定
		bIsInterruptHit        = (RepBits & (1ULL << 24)) != 0;                           // 解包打断判定
		bIsHeal                = (RepBits & (1ULL << 25)) != 0;                           // 解包治疗判定
		bIsShieldApplication   = (RepBits & (1ULL << 26)) != 0;                           // 解包套盾判定
		bIsBackstab            = (RepBits & (1ULL << 27)) != 0;                           // 解包背刺判定
		bIsStealthHit          = (RepBits & (1ULL << 28)) != 0;                           // 解包隐身判定
		bIsTurretDamage        = (RepBits & (1ULL << 29)) != 0;                           // 解包塔伤判定
		bIsFountainDamage      = (RepBits & (1ULL << 30)) != 0;                           // 解包泉水判定
		bBypassesShields       = (RepBits & (1ULL << 31)) != 0;                           // 解包穿盾判定
		bIsFatalHit            = (RepBits & (1ULL << 32)) != 0;                           // 解包致死判定
		bIsNonLethal           = (RepBits & (1ULL << 33)) != 0;                           // 解包锁血判定
		bIsRadialDamage        = (RepBits & (1ULL << 39)) != 0;                           // 解包径向判定
		bIsPhantomHit          = (RepBits & (1ULL << 43)) != 0;                           // 解包羊刀标志
	}

	// 复杂数值字段读写
	if (RepBits & (1ULL << 13)) { Ar << DebuffDamage; }                                   // 读写Debuff伤
	if (RepBits & (1ULL << 14)) { Ar << DebuffDuration; }                                 // 读写Debuff长
	if (RepBits & (1ULL << 15)) { Ar << DebuffFrequency; }                                // 读写Debuff频
	if (RepBits & (1ULL << 34)) { Ar << (uint8&)DamageType; }                             // 读写LoL路径
	if (RepBits & (1ULL << 35))                                                           // 读写宝可梦标签
	{
		if (Ar.IsLoading()) { if (!DamageTypeTag.IsValid()) DamageTypeTag = MakeShared<FGameplayTag>(); }
		DamageTypeTag->NetSerialize(Ar, Map, bOutSuccess);
	}
	if (RepBits & (1ULL << 36)) { Ar << TypeMultiplier; }                                 // 读写倍率
	if (RepBits & (1ULL << 37)) { DeathImpulse.NetSerialize(Ar, Map, bOutSuccess); }       // 读写死亡力
	if (RepBits & (1ULL << 38)) { KnockbackForce.NetSerialize(Ar, Map, bOutSuccess); }     // 读写击退力
	if (RepBits & (1ULL << 40)) { Ar << RadialDamageInnerRadius; }                        // 读写内径
	if (RepBits & (1ULL << 41)) { Ar << RadialDamageOuterRadius; }                        // 读写外径
	if (RepBits & (1ULL << 42)) { RadialDamageOrigin.NetSerialize(Ar, Map, bOutSuccess); } // 读写中心点

	// --- 【Noita 零件数组同步】 ---
	if (RepBits & (1ULL << 44))
	{
		SafeNetSerializeTArray_Default<31>(Ar, AppliedSpellParts);                         // 读写积木数组
	}

	// =========================================================
	// 4. 【初始化 ASC 缓存】
	// =========================================================
	if (Ar.IsLoading())
	{
		AddInstigator(Instigator.Get(), EffectCauser.Get());                              // 初始化ASC指针
	}

	bOutSuccess = true;
	return true;
}