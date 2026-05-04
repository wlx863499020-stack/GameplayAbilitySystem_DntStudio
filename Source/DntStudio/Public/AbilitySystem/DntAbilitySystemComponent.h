// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h" // [补全] 确保头文件级别能直接识别 FGameplayTag 和 FGameplayTagContainer
#include "DntAbilitySystemComponent.generated.h"

//class ULoadScreenSaveGame;
class UGameplayAbility;           // [补全] 前向声明，确保 TSubclassOf<UGameplayAbility> 被正确识别

// 委托声明区 (完全保持你原有的签名)
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);
DECLARE_MULTICAST_DELEGATE(FAbilitiesGiven);
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FAbilityStatusChanged, const FGameplayTag& /*AbilityTag*/, const FGameplayTag& /*StatusTag*/, int32 /*AbilityLevel*/);
DECLARE_MULTICAST_DELEGATE_FourParams(FAbilityEquipped, const FGameplayTag& /*AbilityTag*/, const FGameplayTag& /*Status*/, const FGameplayTag& /*Slot*/, const FGameplayTag& /*PrevSlot*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FDeactivatePassiveAbility, const FGameplayTag& /*AbilityTag*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FActivatePassiveEffect, const FGameplayTag& /*AbilityTag*/, bool /*bActivate*/);

/**
 * UDntAbilitySystemComponent
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent)) // [补全] 暴露给蓝图组件列表，防止挂载异常
class DNTSTUDIO_API UDntAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()	
	
public:
	/* =========================================================================
	 * 1. 核心委托与初始化状态
	 * ========================================================================= */
	void AbilityActorInfoSet();
	
	FEffectAssetTags EffectAssetTags;
	FAbilitiesGiven AbilitiesGivenDelegate;
	FAbilityStatusChanged AbilityStatusChanged;
	FAbilityEquipped AbilityEquipped;
	FDeactivatePassiveAbility DeactivatePassiveAbility;
	FActivatePassiveEffect ActivatePassiveEffect;
	
	bool bStartupAbilitiesGiven = false;

	/* =========================================================================
	 * 2. 技能与属性赋予 (加载与初始化)
	 * ========================================================================= */
	//void AddCharacterAbilitiesFromSaveData(ULoadScreenSaveGame* SaveData);
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities);

	/* =========================================================================
	 * 3. 输入路由拦截 (修复按键没反应的核心关联区)
	 * ========================================================================= */
	// [补全] 必须加上 BlueprintCallable，否则 C++ 和蓝图的 Enhanced Input 无法跨层调用
	UFUNCTION(BlueprintCallable, Category = "Dnt|Abilities|Input")
	void AbilityInputTagPressed(const FGameplayTag& InputTag);

	UFUNCTION(BlueprintCallable, Category = "Dnt|Abilities|Input")
	void AbilityInputTagHeld(const FGameplayTag& InputTag);

	UFUNCTION(BlueprintCallable, Category = "Dnt|Abilities|Input")
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ForEachAbility(const FForEachAbility& Delegate);
	
	/* =========================================================================
	 * 4. Tag 与 槽位数据检索工具
	 * ========================================================================= */
	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	
	// [补全] 暴露给蓝图，UI/技能树 需要据此判断状态
	UFUNCTION(BlueprintCallable, Category = "Dnt|Abilities|Tags")
	FGameplayTag GetStatusFromAbilityTag(const FGameplayTag& AbilityTag);
	
	UFUNCTION(BlueprintCallable, Category = "Dnt|Abilities|Tags")
	FGameplayTag GetSlotFromAbilityTag(const FGameplayTag& AbilityTag);
	
	UFUNCTION(BlueprintCallable, Category = "Dnt|Abilities|Tags")
	bool SlotIsEmpty(const FGameplayTag& Slot);

	bool IsPassiveAbility(const FGameplayAbilitySpec& Spec) const;
	FGameplayAbilitySpec* GetSpecFromAbilityTag(const FGameplayTag& AbilityTag);
	FGameplayAbilitySpec* GetSpecWithSlot(const FGameplayTag& Slot);

	static bool AbilityHasSlot(const FGameplayAbilitySpec& Spec, const FGameplayTag& Slot);
	static bool AbilityHasSlot(FGameplayAbilitySpec* Spec, const FGameplayTag& Slot); // 你的重载版本
	static bool AbilityHasAnySlot(const FGameplayAbilitySpec& Spec);
	
	static void AssignSlotToAbility(FGameplayAbilitySpec& Spec, const FGameplayTag& Slot);
	static void ClearSlot(FGameplayAbilitySpec* Spec);
	void ClearAbilitiesOfSlot(const FGameplayTag& Slot);

	/* =========================================================================
	 * 5. 升级与装备 RPC (网络同步)
	 * ========================================================================= */
	// [补全] 暴露给蓝图，UI点击升级时需要调用
	UFUNCTION(BlueprintCallable, Category = "Dnt|Abilities|Progression")
	void UpgradeAttribute(const FGameplayTag& AttributeTag);

	UFUNCTION(Server, Reliable)
	void ServerUpgradeAttribute(const FGameplayTag& AttributeTag);

	UFUNCTION(BlueprintCallable, Category = "Dnt|Abilities|Progression")
	void UpdateAbilityStatuses(int32 Level);

	UFUNCTION(Server, Reliable)
	void ServerSpendSpellPoint(const FGameplayTag& AbilityTag);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Dnt|Abilities|Equip")
	void ServerEquipAbility(const FGameplayTag& AbilityTag, const FGameplayTag& Slot);

	UFUNCTION(Client, Reliable)
	void ClientEquipAbility(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& Slot, const FGameplayTag& PreviousSlot);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastActivatePassiveEffect(const FGameplayTag& AbilityTag, bool bActivate);

	// [补全] 暴露给蓝图，UI悬浮窗读取技能文本时必须用到
	UFUNCTION(BlueprintCallable, Category = "Dnt|Abilities|UI")
	bool GetDescriptionsByAbilityTag(const FGameplayTag& AbilityTag, FString& OutDescription, FString& OutNextLevelDescription);

protected:

	virtual void OnRep_ActivateAbilities() override;

	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

	UFUNCTION(Client, Reliable)
	void ClientUpdateAbilityStatus(const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 AbilityLevel);
};