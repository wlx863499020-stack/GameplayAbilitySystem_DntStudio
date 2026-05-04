// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/CharacterClassInfo.h"
#include "DntAbilityTypes.h"
#include "DntAbilitySystemLibrary.generated.h"

class UAbilityInfo;
class USpellMenuWidgetController;
class UAbilitySystemComponent;
class UAttributeMenuWidgetController;
class UOverlayWidgetController;
class ULootTiers;
class ULoadScreenSaveGame;
struct FWidgetControllerParams;

UCLASS()
class DNTSTUDIO_API UDntAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/* =========================================================================
	 * 1. UI Controller Factory (UI控制器工厂)
	 * ========================================================================= */

	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static bool MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, ADntHUD*& OutHUD); // 组装UI参数
	
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);                            // 获取主界面控制器
	
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);                // 获取属性菜单控制器

	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static USpellMenuWidgetController* GetSpellMenuWidgetController(const UObject* WorldContextObject);                        // 获取技能菜单控制器

	/* =========================================================================
	 * 2. Class Defaults & Data (属性初始化与资产获取)
	 * ========================================================================= */

	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CC, float Lv, UAbilitySystemComponent* ASC); // 默认属性初始化
	
	//UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|CharacterClassDefaults")
	//static void InitializeDefaultAttributesFromSaveData(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ULoadScreenSaveGame* SG); // 存档数据初始化
	
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|CharacterClassDefaults")
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CC);     // 赋予初始技能
	
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);                                      // 获取职业配置资产
	
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|CharacterClassDefaults")
	static UAbilityInfo* GetAbilityInfo(const UObject* WorldContextObject);                                                    // 获取技能配置资产

	//UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|CharacterClassDefaults", meta = (DefaultToSelf = "WorldContextObject"))
	//static ULootTiers* GetLootTiers(const UObject* WorldContextObject);                                                        // 获取战利品配置资产

	/* =========================================================================
	 * 3. Effect Context Getters (战斗状态读取 - 全部 44 位状态)
	 * ========================================================================= */

	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static EDntDamageType GetDamageType(const FGameplayEffectContextHandle& H);     // 读:LoL路径(枚举)
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static FGameplayTag    GetDamageTypeTag(const FGameplayEffectContextHandle& H);  // 读:元素标签(Tag)
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsBlockedHit(const FGameplayEffectContextHandle& H);             // 读:是否格挡
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsCriticalHit(const FGameplayEffectContextHandle& H);            // 读:是否暴击
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsDodgedHit(const FGameplayEffectContextHandle& H);              // 读:是否闪避
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsInvulnerableHit(const FGameplayEffectContextHandle& H);        // 读:是否无敌
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsShieldBroken(const FGameplayEffectContextHandle& H);           // 读:是否破盾
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsSuccessfulDebuff(const FGameplayEffectContextHandle& H);        // 读:是否成功Debuff
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static float GetDebuffDamage(const FGameplayEffectContextHandle& H);          // 读:Debuff伤害
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static float GetDebuffDuration(const FGameplayEffectContextHandle& H);        // 读:Debuff时长
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static float GetDebuffFrequency(const FGameplayEffectContextHandle& H);       // 读:Debuff频率
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsBasicAttack(const FGameplayEffectContextHandle& H);            // 读:是否平A
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsAbilityDamage(const FGameplayEffectContextHandle& H);          // 读:是否技能伤
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsPeriodicDamage(const FGameplayEffectContextHandle& H);         // 读:是否持续伤(DoT)
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsAoEDamage(const FGameplayEffectContextHandle& H);              // 读:是否AOE伤
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsPetDamage(const FGameplayEffectContextHandle& H);              // 读:是否宠物伤
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsReflectedDamage(const FGameplayEffectContextHandle& H);        // 读:是否反弹伤
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsPhantomHit(const FGameplayEffectContextHandle& H);             // 读:是否羊刀触发
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsExecuteHit(const FGameplayEffectContextHandle& H);             // 读:是否斩杀处决
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  HasLifesteal(const FGameplayEffectContextHandle& H);             // 读:是否触发吸血
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsInterruptHit(const FGameplayEffectContextHandle& H);           // 读:是否打断引导
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsHeal(const FGameplayEffectContextHandle& H);                   // 读:是否治疗效果
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsShieldApplication(const FGameplayEffectContextHandle& H);     // 读:是否正在套盾
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsBackstab(const FGameplayEffectContextHandle& H);               // 读:是否背刺判定
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsStealthHit(const FGameplayEffectContextHandle& H);             // 读:是否隐身攻击
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsTurretDamage(const FGameplayEffectContextHandle& H);           // 读:是否防御塔伤害
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsFountainDamage(const FGameplayEffectContextHandle& H);         // 读:是否泉水伤害
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  BypassesShields(const FGameplayEffectContextHandle& H);          // 读:是否穿透护盾
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsFatalHit(const FGameplayEffectContextHandle& H);               // 读:是否致死打击
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsNonLethal(const FGameplayEffectContextHandle& H);              // 读:是否非致死(锁血)
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static float GetTypeMultiplier(const FGameplayEffectContextHandle& H);        // 读:属性克制倍率
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static FVector GetDeathImpulse(const FGameplayEffectContextHandle& H);        // 读:死亡冲量向量
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static FVector GetKnockbackForce(const FGameplayEffectContextHandle& H);      // 读:击退力量向量
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static bool  IsRadialDamage(const FGameplayEffectContextHandle& H);          // 读:是否径向伤害
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static float GetRadialDamageInnerRadius(const FGameplayEffectContextHandle& H); // 读:径向内半径
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static float GetRadialDamageOuterRadius(const FGameplayEffectContextHandle& H); // 读:径向外半径
	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayEffects") static FVector GetRadialDamageOrigin(const FGameplayEffectContextHandle& H);      // 读:径向来源中心

	/* =========================================================================
	 * 4. Effect Context Setters (状态写入 - 严格使用引用参数)
	 * ========================================================================= */

	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetDamageType(UPARAM(ref) FGameplayEffectContextHandle& H, EDntDamageType T);   // 写:LoL路径(枚举)
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetDamageTypeTag(UPARAM(ref) FGameplayEffectContextHandle& H, const FGameplayTag& T); // 写:元素标签(Tag)
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);         // 写:格挡
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);        // 写:暴击
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsDodgedHit(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);          // 写:闪避
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsInvulnerableHit(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);    // 写:无敌
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetShieldBroken(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);         // 写:破盾
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsSuccessfulDebuff(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);   // 写:Debuff成功
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetDebuffDamage(UPARAM(ref) FGameplayEffectContextHandle& H, float InV);        // 写:Debuff伤害
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetDebuffDuration(UPARAM(ref) FGameplayEffectContextHandle& H, float InV);      // 写:Debuff时长
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetDebuffFrequency(UPARAM(ref) FGameplayEffectContextHandle& H, float InV);     // 写:Debuff频率
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsBasicAttack(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);        // 写:平A判定
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsAbilityDamage(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);      // 写:技能判定
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsPeriodicDamage(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);     // 写:DoT判定
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsAoEDamage(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);          // 写:AOE判定
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsPetDamage(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);          // 写:宠物判定
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsReflectedDamage(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);    // 写:反弹判定
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsPhantomHit(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);         // 写:羊刀判定
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsExecuteHit(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);         // 写:斩杀判定
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetHasLifesteal(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);         // 写:吸血判定
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsInterruptHit(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);       // 写:打断判定
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsHeal(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);               // 写:治疗判定
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsShieldApplication(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);   // 写:套盾判定
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsBackstab(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);           // 写:背刺判定
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsStealthHit(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);         // 写:隐身攻击判定
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsTurretDamage(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);       // 写:塔伤判定
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsFountainDamage(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);     // 写:泉水伤判定
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetBypassesShields(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);       // 写:穿盾判定
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsFatalHit(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);           // 写:致死判定
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsNonLethal(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);          // 写:锁血判定
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetTypeMultiplier(UPARAM(ref) FGameplayEffectContextHandle& H, float InV);      // 写:克制倍率
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetDeathImpulse(UPARAM(ref) FGameplayEffectContextHandle& H, const FVector& InV);    // 写:死亡冲量
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetKnockbackForce(UPARAM(ref) FGameplayEffectContextHandle& H, const FVector& InV);  // 写:击退力
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetIsRadialDamage(UPARAM(ref) FGameplayEffectContextHandle& H, bool bIn);        // 写:是否径向
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetRadialDamageInnerRadius(UPARAM(ref) FGameplayEffectContextHandle& H, float InV); // 写:内径
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetRadialDamageOuterRadius(UPARAM(ref) FGameplayEffectContextHandle& H, float InV); // 写:外径
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayEffects") static void SetRadialDamageOrigin(UPARAM(ref) FGameplayEffectContextHandle& H, const FVector& InV); // 写:径源

	/* =========================================================================
	 * 5. Gameplay Mechanics & Math (通用游戏机制与数学算法)
	 * ========================================================================= */
	
	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayMechanics")
	static void GetLivePlayersWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutActors, const TArray<AActor*>& IgnoreActors, float Radius, const FVector& Origin); // 获取范围内活人

	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|GameplayMechanics")
	static void GetClosestTargets(int32 MaxTargets, const TArray<AActor*>& Actors, TArray<AActor*>& OutTargets, const FVector& Origin); // 获取最近目标列表

	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayMechanics")
	static bool IsNotFriend(AActor* FirstActor, AActor* SecondActor);                                                            // 友军判定

	UFUNCTION(BlueprintCallable, Category="DntAbilitySystemLibrary|DamageEffect")
	static FGameplayEffectContextHandle ApplyDamageEffect(const FDamageEffectParams& Params);                   // 执行伤害效果应用

	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayMechanics")
	static TArray<FRotator> EvenlySpacedRotators(const FVector& Forward, const FVector& Axis, float Spread, int32 Num);         // 均匀旋转计算

	UFUNCTION(BlueprintPure, Category="DntAbilitySystemLibrary|GameplayMechanics")
	static TArray<FVector> EvenlyRotatedVectors(const FVector& Forward, const FVector& Axis, float Spread, int32 Num);           // 均匀向量计算

	static int32 GetXPRewardForClassAndLevel(const UObject* WorldContextObject, ECharacterClass CC, int32 Lv);                                 // 获取经验奖励值

	/* =========================================================================
	 * 6. Damage Effect Params Helpers (数据包便捷助手)
	 * ========================================================================= */

	UFUNCTION(BlueprintCallable, Category = "DntAbilitySystemLibrary|DamageEffect")
	static void SetIsRadialDamageEffectParam(UPARAM(ref) FDamageEffectParams& Params, bool bIsR, float Inner, float Outer, FVector Origin); // 设置径向参数
	UFUNCTION(BlueprintCallable, Category = "DntAbilitySystemLibrary|DamageEffect")
	static void SetKnockbackDirection(UPARAM(ref) FDamageEffectParams& Params, FVector Dir, float Mag = 0.f);                    // 设置击退方向
	UFUNCTION(BlueprintCallable, Category = "DntAbilitySystemLibrary|DamageEffect")
	static void SetDeathImpulseDirection(UPARAM(ref) FDamageEffectParams& Params, FVector Dir, float Mag = 0.f);                 // 设置死亡冲量方向
	UFUNCTION(BlueprintCallable, Category = "DntAbilitySystemLibrary|DamageEffect")
	static void SetTargetEffectParamsASC(UPARAM(ref) FDamageEffectParams& Params, UAbilitySystemComponent* ASC);                 // 设置目标ASC
};