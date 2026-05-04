// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "DntAbilityTypes.generated.h"

class UGameplayEffect;
class UNiagaraSystem;

// =========================================================
// 1. 英雄联盟核心伤害路径枚举 (决定计算分支)
// =========================================================
UENUM(BlueprintType)
enum class EDntDamageType : uint8
{
	Physical    UMETA(DisplayName = "物理伤害 (AD)"),                                      // 0. 物理伤害路径
	Magic       UMETA(DisplayName = "魔法伤害 (AP)"),                                      // 1. 魔法伤害路径
	TrueDamage  UMETA(DisplayName = "真实伤害 (True)"),                                    // 2. 真实伤害路径
	None        UMETA(DisplayName = "无伤害")                                              // 3. 初始/占位符
};

// =========================================================
// 2. Noita 风格：法术零件类型
// =========================================================
UENUM(BlueprintType)
enum class ESpellPartType : uint8
{
	Projectile    UMETA(DisplayName = "投射物本体"),                                      // 法术主体(如火球)
	Modifier      UMETA(DisplayName = "修正器"),                                          // 数值修正(如伤害+)
	Element       UMETA(DisplayName = "元素注入"),                                        // 元素改变(如转火)
	Trigger       UMETA(DisplayName = "触发器")                                           // 逻辑链接(如碰撞触发)
};

// =========================================================
// 3. Noita 风格：单个法术零件定义 (积木块)
// =========================================================
USTRUCT(BlueprintType)
struct FDntSpellPart
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESpellPartType PartType = ESpellPartType::Modifier;                                    // 零件类别判定

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag PartTag;                                                                  // 关联的元素/功能标签

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageModifier = 0.f;                                                            // 提供的伤害增量

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpeedModifier = 1.0f;                                                            // 提供的速度倍率

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraSystem> VisualEffect;                                               // 携带的附加视觉特效

	// [修复核心] 告诉引擎底层网络如何打包这个积木数组，彻底消除 C2679 刷屏报错
	friend FArchive& operator<<(FArchive& Ar, FDntSpellPart& Part)
	{
		Ar << Part.PartType;
		Ar << Part.PartTag;
		Ar << Part.DamageModifier;
		Ar << Part.SpeedModifier;
		Ar << Part.VisualEffect;
		return Ar;
	}
};
// =========================================================
// 4. 伤害效果参数结构体 (包含 Noita 零件包载荷)
// =========================================================
USTRUCT(BlueprintType)
struct FDamageEffectParams
{
	GENERATED_BODY()

	FDamageEffectParams(){}

	UPROPERTY(BlueprintReadWrite) TObjectPtr<UObject> WorldContextObject = nullptr;             // 1. 世界上下文
	UPROPERTY(BlueprintReadWrite) TSubclassOf<UGameplayEffect> DamageGameplayEffectClass = nullptr; // 2. 伤害GE
	UPROPERTY(BlueprintReadWrite) TSubclassOf<UGameplayEffect> DebuffGameplayEffectClass = nullptr; // 3. 状态GE
	UPROPERTY(BlueprintReadWrite) TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent; // 4. 来源ASC
	UPROPERTY(BlueprintReadWrite) TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent; // 5. 目标ASC

	UPROPERTY(BlueprintReadWrite) float BaseDamage = 0.f;                                       // 6. 基础伤害
	UPROPERTY(BlueprintReadWrite) float AbilityLevel = 1.f;                                     // 7. 技能等级
	UPROPERTY(BlueprintReadWrite) float SourceLevel = 1.f;                                      // 8. 来源等级
	UPROPERTY(BlueprintReadWrite) FGameplayTag DamageType = FGameplayTag();                     // 9. 宝可梦元素

	UPROPERTY(BlueprintReadWrite) TArray<FDntSpellPart> AppliedSpellParts;                      // 10. Noita零件包

	UPROPERTY(BlueprintReadWrite) float DebuffChance = 0.f;                                     // 11. Debuff率
	UPROPERTY(BlueprintReadWrite) float DebuffDamage = 0.f;                                     // 12. Debuff伤
	UPROPERTY(BlueprintReadWrite) float DebuffDuration = 0.f;                                   // 13. Debuff长
	UPROPERTY(BlueprintReadWrite) float DebuffFrequency = 0.f;                                  // 14. Debuff频
	UPROPERTY(BlueprintReadWrite) float DeathImpulseMagnitude = 0.f;                            // 15. 死亡力
	UPROPERTY(BlueprintReadWrite) FVector DeathImpulse = FVector::ZeroVector;                   // 16. 死亡向量
	UPROPERTY(BlueprintReadWrite) float KnockbackForceMagnitude = 0.f;                          // 17. 击退力
	UPROPERTY(BlueprintReadWrite) float KnockbackChance = 0.f;                                  // 18. 击退率
	UPROPERTY(BlueprintReadWrite) FVector KnockbackForce = FVector::ZeroVector;                 // 19. 击退向量

	UPROPERTY(BlueprintReadWrite) bool bIsRadialDamage = false;                                 // 20. 是否径向
	UPROPERTY(BlueprintReadWrite) float RadialDamageInnerRadius = 0.f;                          // 21. 径向内径
	UPROPERTY(BlueprintReadWrite) float RadialDamageOuterRadius = 0.f;                          // 22. 径向外径
	UPROPERTY(BlueprintReadWrite) FVector RadialDamageOrigin = FVector::ZeroVector;             // 23. 径向原点
	UPROPERTY(BlueprintReadWrite) bool bIsBasicAttack = false;                                  // 24. 是否平A
};

// =========================================================
// 5. 自定义 EffectContext (战斗瞬间 45 位全量状态位)
// =========================================================
USTRUCT(BlueprintType)
struct FDntGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	virtual UScriptStruct* GetScriptStruct() const override { return FDntGameplayEffectContext::StaticStruct(); }
	virtual FDntGameplayEffectContext* Duplicate() const override
	{
		FDntGameplayEffectContext* NewContext = new FDntGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult()) NewContext->AddHitResult(*GetHitResult(), true);
		return NewContext;
	}
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;

	/* --- Getters --- */
	EDntDamageType GetDamageType() const { return DamageType; }                            // 读:LoL路径枚举
	TSharedPtr<FGameplayTag> GetDamageTypeTag() const { return DamageTypeTag; }            // 读:元素标签指针
	const TArray<FDntSpellPart>& GetAppliedSpellParts() const { return AppliedSpellParts; } // 读:Noita零件包
	bool IsBlockedHit() const { return bIsBlockedHit; }                                    // 读:是否格挡
	bool IsCriticalHit() const { return bIsCriticalHit; }                                  // 读:是否暴击
	bool IsDodgedHit() const { return bIsDodgedHit; }                                      // 读:是否闪避
	bool IsInvulnerableHit() const { return bIsInvulnerableHit; }                          // 读:是否无敌
	bool IsShieldBroken() const { return bIsShieldBroken; }                                // 读:是否破盾
	bool IsSuccessfulDebuff() const { return bIsSuccessfulDebuff; }                        // 读:Debuff成功
	float GetDebuffDamage() const { return DebuffDamage; }                                 // 读:Debuff伤害
	float GetDebuffDuration() const { return DebuffDuration; }                             // 读:Debuff时长
	float GetDebuffFrequency() const { return DebuffFrequency; }                           // 读:Debuff频率
	bool IsBasicAttack() const { return bIsBasicAttack; }                                  // 读:是否平A
	bool IsAbilityDamage() const { return bIsAbilityDamage; }                              // 读:是否技能伤
	bool IsPeriodicDamage() const { return bIsPeriodicDamage; }                            // 读:是否持续伤
	bool IsAoEDamage() const { return bIsAoEDamage; }                                      // 读:是否AOE
	bool IsPetDamage() const { return bIsPetDamage; }                                      // 读:是否宠物伤
	bool IsReflectedDamage() const { return bIsReflectedDamage; }                          // 读:是否反弹
	bool IsExecuteHit() const { return bIsExecuteHit; }                                    // 读:是否斩杀
	bool HasLifesteal() const { return bHasLifesteal; }                                    // 读:是否吸血
	bool IsInterruptHit() const { return bIsInterruptHit; }                                // 读:是否打断
	bool IsHeal() const { return bIsHeal; }                                                // 读:是否治疗
	bool IsShieldApplication() const { return bIsShieldApplication; }                      // 读:是否套盾
	bool IsBackstab() const { return bIsBackstab; }                                        // 读:是否背刺
	bool IsStealthHit() const { return bIsStealthHit; }                                    // 读:是否隐身攻击
	bool IsTurretDamage() const { return bIsTurretDamage; }                                // 读:是否塔伤
	bool IsFountainDamage() const { return bIsFountainDamage; }                            // 读:是否泉水伤
	bool BypassesShields() const { return bBypassesShields; }                              // 读:是否穿盾
	bool IsFatalHit() const { return bIsFatalHit; }                                        // 读:是否致死
	bool IsNonLethal() const { return bIsNonLethal; }                                      // 读:是否锁血
	float GetTypeMultiplier() const { return TypeMultiplier; }                             // 读:克制倍率
	bool IsPhantomHit() const { return bIsPhantomHit; }                                    // 读:是否羊刀触发
	FVector GetDeathImpulse() const { return DeathImpulse; }                               // 读:死亡冲量
	FVector GetKnockbackForce() const { return KnockbackForce; }                           // 读:击退力
	bool IsRadialDamage() const { return bIsRadialDamage; }                                // 读:是否径向
	float GetRadialDamageInnerRadius() const { return RadialDamageInnerRadius; }           // 读:径向内径
	float GetRadialDamageOuterRadius() const { return RadialDamageOuterRadius; }           // 读:径向外径
	FVector GetRadialDamageOrigin() const { return RadialDamageOrigin; }                   // 读:径向原点

	/* --- Setters --- */
	void SetDamageType(EDntDamageType InType) { DamageType = InType; }
	void SetDamageTypeTag(const FGameplayTag& InTag) { DamageTypeTag = MakeShared<FGameplayTag>(InTag); }
	void SetAppliedSpellParts(const TArray<FDntSpellPart>& InParts) { AppliedSpellParts = InParts; }
	void SetIsBlockedHit(bool bIn) { bIsBlockedHit = bIn; }
	void SetIsCriticalHit(bool bIn) { bIsCriticalHit = bIn; }
	void SetIsDodgedHit(bool bIn) { bIsDodgedHit = bIn; }
	void SetIsInvulnerableHit(bool bIn) { bIsInvulnerableHit = bIn; }
	void SetShieldBroken(bool bIn) { bIsShieldBroken = bIn; }
	void SetIsSuccessfulDebuff(bool bIn) { bIsSuccessfulDebuff = bIn; }
	void SetDebuffDamage(float InDamage) { DebuffDamage = InDamage; }
	void SetDebuffDuration(float InDuration) { DebuffDuration = InDuration; }
	void SetDebuffFrequency(float InFreq) { DebuffFrequency = InFreq; }
	void SetIsBasicAttack(bool bIn) { bIsBasicAttack = bIn; }
	void SetIsAbilityDamage(bool bIn) { bIsAbilityDamage = bIn; }
	void SetIsPeriodicDamage(bool bIn) { bIsPeriodicDamage = bIn; }
	void SetIsAoEDamage(bool bIn) { bIsAoEDamage = bIn; }
	void SetIsPetDamage(bool bIn) { bIsPetDamage = bIn; }
	void SetIsReflectedDamage(bool bIn) { bIsReflectedDamage = bIn; }
	void SetIsExecuteHit(bool bIn) { bIsExecuteHit = bIn; }
	void SetHasLifesteal(bool bIn) { bHasLifesteal = bIn; }
	void SetIsInterruptHit(bool bIn) { bIsInterruptHit = bIn; }
	void SetIsHeal(bool bIn) { bIsHeal = bIn; }
	void SetIsShieldApplication(bool bIn) { bIsShieldApplication = bIn; }
	void SetIsBackstab(bool bIn) { bIsBackstab = bIn; }
	void SetIsStealthHit(bool bIn) { bIsStealthHit = bIn; }
	void SetIsTurretDamage(bool bIn) { bIsTurretDamage = bIn; }
	void SetIsFountainDamage(bool bIn) { bIsFountainDamage = bIn; }
	void SetBypassesShields(bool bIn) { bBypassesShields = bIn; }
	void SetIsFatalHit(bool bIn) { bIsFatalHit = bIn; }
	void SetIsNonLethal(bool bIn) { bIsNonLethal = bIn; }
	void SetTypeMultiplier(float InMult) { TypeMultiplier = InMult; }
	void SetIsPhantomHit(bool bIn) { bIsPhantomHit = bIn; }
	void SetDeathImpulse(const FVector& InImpulse) { DeathImpulse = InImpulse; }
	void SetKnockbackForce(const FVector& InForce) { KnockbackForce = InForce; }
	void SetIsRadialDamage(bool bIn) { bIsRadialDamage = bIn; }
	void SetRadialDamageInnerRadius(float InRadius) { RadialDamageInnerRadius = InRadius; }
	void SetRadialDamageOuterRadius(float InRadius) { RadialDamageOuterRadius = InRadius; }
	void SetRadialDamageOrigin(const FVector& InOrigin) { RadialDamageOrigin = InOrigin; }

protected:
	// --- 数据持久化成员 (严格对齐 45 位掩码) ---
	UPROPERTY() EDntDamageType DamageType = EDntDamageType::None;                          // 34.LoL枚举存储
	TSharedPtr<FGameplayTag> DamageTypeTag;                                                // 35.宝可梦标签存储
	UPROPERTY() float TypeMultiplier = 1.0f;                                               // 36.克制倍率存储
	UPROPERTY() bool bIsPhantomHit = false;                                                // 43.羊刀打击存储
	UPROPERTY(BlueprintReadWrite) TArray<FDntSpellPart> AppliedSpellParts;                 // 44.Noita零件包存储

	UPROPERTY() bool bIsBlockedHit = false;                                                // 7.格挡存储
	UPROPERTY() bool bIsCriticalHit = false;                                               // 8.暴击存储
	UPROPERTY() bool bIsDodgedHit = false;                                                 // 9.闪避存储
	UPROPERTY() bool bIsInvulnerableHit = false;                                           // 10.无敌存储
	UPROPERTY() bool bIsShieldBroken = false;                                              // 11.破盾存储
	UPROPERTY() bool bIsSuccessfulDebuff = false;                                          // 12.Debuff成功存储
	UPROPERTY() float DebuffDamage = 0.f;                                                  // 13.Debuff伤害
	UPROPERTY() float DebuffDuration = 0.f;                                                // 14.Debuff时长
	UPROPERTY() float DebuffFrequency = 0.f;                                               // 15.Debuff频率

	UPROPERTY() bool bIsBasicAttack = false;                                               // 16.普攻判定位
	UPROPERTY() bool bIsAbilityDamage = false;                                             // 17.技能判定位
	UPROPERTY() bool bIsPeriodicDamage = false;                                            // 18.周期判定
	UPROPERTY() bool bIsAoEDamage = false;                                                 // 19.AOE判定
	UPROPERTY() bool bIsPetDamage = false;                                                 // 20.宠物判定
	UPROPERTY() bool bIsReflectedDamage = false;                                           // 21.反弹判定

	UPROPERTY() bool bIsExecuteHit = false;                                                // 22.斩杀判定
	UPROPERTY() bool bHasLifesteal = false;                                                // 23.吸血判定
	UPROPERTY() bool bIsInterruptHit = false;                                              // 24.打断判定

	UPROPERTY() bool bIsHeal = false;                                                      // 25.治疗判定
	UPROPERTY() bool bIsShieldApplication = false;                                         // 26.套盾判定
	UPROPERTY() bool bIsBackstab = false;                                                  // 27.背刺判定
	UPROPERTY() bool bIsStealthHit = false;                                                // 28.隐身判定

	UPROPERTY() bool bIsTurretDamage = false;                                              // 29.塔伤判定
	UPROPERTY() bool bIsFountainDamage = false;                                            // 30.泉水判定
	UPROPERTY() bool bBypassesShields = false;                                             // 31.穿盾判定
	UPROPERTY() bool bIsFatalHit = false;                                                  // 32.致死判定
	UPROPERTY() bool bIsNonLethal = false;                                                 // 33.锁血判定

	UPROPERTY() FVector DeathImpulse = FVector::ZeroVector;                                // 37.冲量存储
	UPROPERTY() FVector KnockbackForce = FVector::ZeroVector;                              // 38.击退存储
	UPROPERTY() bool bIsRadialDamage = false;                                              // 39.径向标志
	UPROPERTY() float RadialDamageInnerRadius = 0.f;                                       // 40.内径存储
	UPROPERTY() float RadialDamageOuterRadius = 0.f;                                       // 41.外径存储
	UPROPERTY() FVector RadialDamageOrigin = FVector::ZeroVector;                          // 42.原点存储
};

template<>
struct TStructOpsTypeTraits<FDntGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FDntGameplayEffectContext>
{
	enum { WithNetSerializer = true, WithCopy = true };
};