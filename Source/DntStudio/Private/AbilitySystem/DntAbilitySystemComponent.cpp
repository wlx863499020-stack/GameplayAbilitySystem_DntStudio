// DntStudio

#include "AbilitySystem/DntAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "DntGameplayTags.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/DntAbilitySystemLibrary.h"
#include "AbilitySystem/Abilities/DntGameplayAbility.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "DntStudio/DntLogChannals.h" // 保持你的拼写
//#include "Game/LoadScreenSaveGame.h"  // [补全] 联系上存档系统文件
#include "Interaction/PlayerInterface.h"

/* =========================================================================
 * 1. Lifecycle & Initialization (生命周期与初始化)
 * ========================================================================= */

void UDntAbilitySystemComponent::AbilityActorInfoSet() 
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UDntAbilitySystemComponent::ClientEffectApplied);
}

void UDntAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	if (!bStartupAbilitiesGiven)
	{
		bStartupAbilitiesGiven = true;
		AbilitiesGivenDelegate.Broadcast();                                               // 广播能力已赋予
	}
}

void UDntAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UDntGameplayAbility* DntAbility = Cast<UDntGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(DntAbility->StartupInputTag);   // 绑定初始输入
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(FDntGameplayTags::Get().Abilities_Status_Equipped);
			GiveAbility(AbilitySpec);
		}
	}
	bStartupAbilitiesGiven = true;
	AbilitiesGivenDelegate.Broadcast();
}

void UDntAbilitySystemComponent::AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupPassiveAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(FDntGameplayTags::Get().Abilities_Status_Equipped);
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

// [补全] 存档系统对接：已解封，确保读取存档时技能不会丢失
/*void UDntAbilitySystemComponent::AddCharacterAbilitiesFromSaveData(ULoadScreenSaveGame* SaveData)
{
	for (const FSavedAbility& Data : SaveData->SavedAbilities)
	{
		const TSubclassOf<UGameplayAbility> LoadedAbilityClass = Data.GameplayAbility;
		FGameplayAbilitySpec LoadedSpec = FGameplayAbilitySpec(LoadedAbilityClass, Data.AbilityLevel);

		LoadedSpec.GetDynamicSpecSourceTags().AddTag(Data.AbilitySlot);
		LoadedSpec.GetDynamicSpecSourceTags().AddTag(Data.AbilityStatus);
		if (Data.AbilityType == FDntGameplayTags::Get().Abilities_Type_Offensive)
		{
			GiveAbility(LoadedSpec);
		}
		else if (Data.AbilityType == FDntGameplayTags::Get().Abilities_Type_Passive)
		{
			if (Data.AbilityStatus.MatchesTagExact(FDntGameplayTags::Get().Abilities_Status_Equipped))
			{
				GiveAbilityAndActivateOnce(LoadedSpec);
				MulticastActivatePassiveEffect(Data.AbilityTag, true);
			}
			else { GiveAbility(LoadedSpec); }
		}
	}
	bStartupAbilitiesGiven = true;
	AbilitiesGivenDelegate.Broadcast();
}
*/
/* =========================================================================
 * 2. Input Handling (输入处理 - 解决右键失效的关键)
 * ========================================================================= */

void UDntAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(Spec);

			if (Spec.IsActive())
			{
				InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, FPredictionKey());
			}
			else
			{
				TryActivateAbility(Spec.Handle);
			}
		}
	}
}

void UDntAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(Spec);

			if (!Spec.IsActive()) 
			{
				TryActivateAbility(Spec.Handle);
			}
		}
	}
}

void UDntAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	// 强制探针：只要你手松开，这里必须弹字！
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("松手了！Tag: %s"), *InputTag.ToString()));
	
	if (!InputTag.IsValid()) return;

	FScopedAbilityListLock ActiveScopeLoc(*this);

	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(Spec);
			
		}
	}
}


/* =========================================================================
 * 3. Attribute Upgrading (属性升级逻辑)
 * ========================================================================= */

void UDntAbilitySystemComponent::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	if (GetAvatarActor()->Implements<UPlayerInterface>())
	{
		if (IPlayerInterface::Execute_GetAttributePoints(GetAvatarActor()) > 0)
		{
			ServerUpgradeAttribute(AttributeTag);                                         // 发送升级请求
		}
	}
}

void UDntAbilitySystemComponent::ServerUpgradeAttribute_Implementation(const FGameplayTag& AttributeTag)
{
	FGameplayEventData Payload;
	Payload.EventTag = AttributeTag; Payload.EventMagnitude = 1.f;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActor(), AttributeTag, Payload);
	if (GetAvatarActor()->Implements<UPlayerInterface>())
	{
		IPlayerInterface::Execute_AddToAttributePoints(GetAvatarActor(), -1);             // 扣除点数
	}
}

/* =========================================================================
 * 4. Slot & Status Management (槽位与状态管理)
 * ========================================================================= */

bool UDntAbilitySystemComponent::SlotIsEmpty(const FGameplayTag& Slot)
{
	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (AbilityHasSlot(&Spec, Slot)) return false;                                    // 检查槽位
	}
	return true;
}

bool UDntAbilitySystemComponent::AbilityHasSlot(FGameplayAbilitySpec* Spec, const FGameplayTag& Slot)
{
	return Spec->GetDynamicSpecSourceTags().HasTagExact(Slot);                            // 判定是否有指定槽位
}

bool UDntAbilitySystemComponent::AbilityHasSlot(const FGameplayAbilitySpec& Spec, const FGameplayTag& Slot)
{
	return Spec.GetDynamicSpecSourceTags().HasTagExact(Slot);
}

bool UDntAbilitySystemComponent::AbilityHasAnySlot(const FGameplayAbilitySpec& Spec)
{
	return Spec.GetDynamicSpecSourceTags().HasTag(FGameplayTag::RequestGameplayTag(FName("InputTag")));
}

FGameplayAbilitySpec* UDntAbilitySystemComponent::GetSpecWithSlot(const FGameplayTag& Slot)
{
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.GetDynamicSpecSourceTags().HasTagExact(Slot)) return &Spec;
	}
	return nullptr;
}

void UDntAbilitySystemComponent::ClearSlot(FGameplayAbilitySpec* Spec)
{
	const FGameplayTag Slot = GetInputTagFromSpec(*Spec);
	Spec->GetDynamicSpecSourceTags().RemoveTag(Slot);                                     // 清除槽位
}

void UDntAbilitySystemComponent::ClearAbilitiesOfSlot(const FGameplayTag& Slot)
{
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (AbilityHasSlot(&Spec, Slot)) { ClearSlot(&Spec); }                            // 批量清除槽位
	}
}

void UDntAbilitySystemComponent::AssignSlotToAbility(FGameplayAbilitySpec& Spec, const FGameplayTag& Slot)
{
	ClearSlot(&Spec);
	Spec.GetDynamicSpecSourceTags().AddTag(Slot);                                         // 赋予槽位
}

/* =========================================================================
 * 5. Tag & Spec Queries (标签与实例查询)
 * ========================================================================= */

FGameplayTag UDntAbilitySystemComponent::GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	if (AbilitySpec.Ability)
	{
		// [修复] 使用 GetAssetTags() 替代已被私有化的 AbilityTags
		for (FGameplayTag Tag : AbilitySpec.Ability.Get()->GetAssetTags())
		{
			if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities")))) return Tag;
		}
	}
	return FGameplayTag();
}

FGameplayTag UDntAbilitySystemComponent::GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	for (FGameplayTag Tag : AbilitySpec.GetDynamicSpecSourceTags())
	{
		if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("InputTag")))) return Tag;
	}
	return FGameplayTag();
}

FGameplayTag UDntAbilitySystemComponent::GetStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	for (FGameplayTag StatusTag : AbilitySpec.GetDynamicSpecSourceTags())
	{
		if (StatusTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities.Status")))) return StatusTag;
	}
	return FGameplayTag();
}

FGameplayTag UDntAbilitySystemComponent::GetStatusFromAbilityTag(const FGameplayTag& AbilityTag)
{
	if (const FGameplayAbilitySpec* Spec = GetSpecFromAbilityTag(AbilityTag)) { return GetStatusFromSpec(*Spec); }
	return FGameplayTag();
}

FGameplayTag UDntAbilitySystemComponent::GetSlotFromAbilityTag(const FGameplayTag& AbilityTag)
{
	if (const FGameplayAbilitySpec* Spec = GetSpecFromAbilityTag(AbilityTag)) { return GetInputTagFromSpec(*Spec); }
	return FGameplayTag();
}

FGameplayAbilitySpec* UDntAbilitySystemComponent::GetSpecFromAbilityTag(const FGameplayTag& AbilityTag)
{
	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		// [修复] 同上，使用 GetAssetTags()
		for (FGameplayTag Tag : AbilitySpec.Ability.Get()->GetAssetTags())
		{
			if (Tag.MatchesTag(AbilityTag)) return &AbilitySpec;                          // 匹配技能标签
		}
	}
	return nullptr;
}

/* =========================================================================
 * 6. UI & Descriptions (UI描述与菜单)
 * ========================================================================= */

bool UDntAbilitySystemComponent::GetDescriptionsByAbilityTag(const FGameplayTag& AbilityTag, FString& OutDescription, FString& OutNextLevelDescription)
{
	if (const FGameplayAbilitySpec* AbilitySpec = GetSpecFromAbilityTag(AbilityTag))
	{
		if(UDntGameplayAbility* DntAbility = Cast<UDntGameplayAbility>(AbilitySpec->Ability))
		{
			OutDescription = DntAbility->GetDescription(AbilitySpec->Level);
			OutNextLevelDescription = DntAbility->GetNextLevelDescription(AbilitySpec->Level + 1);
			return true;
		}
	}
	const UAbilityInfo* AbilityInfo = UDntAbilitySystemLibrary::GetAbilityInfo(GetAvatarActor());
	if (!AbilityTag.IsValid() || AbilityTag.MatchesTagExact(FDntGameplayTags::Get().Abilities_None)) { OutDescription = FString(); }
	else { OutDescription = UDntGameplayAbility::GetLockedDescription(AbilityInfo->FindAbilityInfoForTag(AbilityTag).LevelRequirement); }
	OutNextLevelDescription = FString();
	return false;
}

void UDntAbilitySystemComponent::UpdateAbilityStatuses(int32 Level)
{
	UAbilityInfo* AbilityInfo = UDntAbilitySystemLibrary::GetAbilityInfo(GetAvatarActor());
	for (const FDntAbilityInfo& Info : AbilityInfo->AbilityInformation)
	{
		if (!Info.AbilityTag.IsValid() || Level < Info.LevelRequirement) continue;
		if (GetSpecFromAbilityTag(Info.AbilityTag) == nullptr)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Info.Ability, 1);
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(FDntGameplayTags::Get().Abilities_Status_Eligible);
			GiveAbility(AbilitySpec);
			MarkAbilitySpecDirty(AbilitySpec);
			ClientUpdateAbilityStatus(Info.AbilityTag, FDntGameplayTags::Get().Abilities_Status_Eligible, 1);
		}
	}
}

/* =========================================================================
 * 7. Server & Client RPCs (网络同步逻辑)
 * ========================================================================= */

void UDntAbilitySystemComponent::ServerSpendSpellPoint_Implementation(const FGameplayTag& AbilityTag)
{
	if (FGameplayAbilitySpec* AbilitySpec = GetSpecFromAbilityTag(AbilityTag))
	{
		if (GetAvatarActor()->Implements<UPlayerInterface>()) { IPlayerInterface::Execute_AddToSpellPoints(GetAvatarActor(), -1); }
		const FDntGameplayTags& Tags = FDntGameplayTags::Get();
		FGameplayTag Status = GetStatusFromSpec(*AbilitySpec);
		if (Status.MatchesTagExact(Tags.Abilities_Status_Eligible))
		{
			AbilitySpec->GetDynamicSpecSourceTags().RemoveTag(Tags.Abilities_Status_Eligible);
			AbilitySpec->GetDynamicSpecSourceTags().AddTag(Tags.Abilities_Status_Unlocked);
			Status = Tags.Abilities_Status_Unlocked;
		}
		else if (Status.MatchesTagExact(Tags.Abilities_Status_Equipped) || Status.MatchesTagExact(Tags.Abilities_Status_Unlocked))
		{
			AbilitySpec->Level += 1;
		}
		ClientUpdateAbilityStatus(AbilityTag, Status, AbilitySpec->Level);
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

void UDntAbilitySystemComponent::ServerEquipAbility_Implementation(const FGameplayTag& AbilityTag, const FGameplayTag& Slot)
{
	if (FGameplayAbilitySpec* AbilitySpec = GetSpecFromAbilityTag(AbilityTag))
	{
		const FDntGameplayTags& Tags = FDntGameplayTags::Get();
		const FGameplayTag& PrevSlot = GetInputTagFromSpec(*AbilitySpec);
		const FGameplayTag& Status = GetStatusFromSpec(*AbilitySpec);

		if (Status == Tags.Abilities_Status_Equipped || Status == Tags.Abilities_Status_Unlocked || Status == Tags.Abilities_Status_Eligible)
		{
			if (!SlotIsEmpty(Slot))
			{
				if (FGameplayAbilitySpec* SpecWithSlot = GetSpecWithSlot(Slot))
				{
					if (AbilityTag.MatchesTagExact(GetAbilityTagFromSpec(*SpecWithSlot)))
					{
						ClientEquipAbility(AbilityTag, Tags.Abilities_Status_Equipped, Slot, PrevSlot);
						return;
					}
					
					if (IsPassiveAbility(*SpecWithSlot))
					{
						MulticastActivatePassiveEffect(GetAbilityTagFromSpec(*SpecWithSlot), false);
						DeactivatePassiveAbility.Broadcast(GetAbilityTagFromSpec(*SpecWithSlot));
					}
					ClearSlot(SpecWithSlot);
				}
			}

			if (!AbilityHasAnySlot(*AbilitySpec)) 
			{
				if (IsPassiveAbility(*AbilitySpec))
				{
					TryActivateAbility(AbilitySpec->Handle);
					MulticastActivatePassiveEffect(AbilityTag, true);
				}
				AbilitySpec->GetDynamicSpecSourceTags().RemoveTag(GetStatusFromSpec(*AbilitySpec));
				AbilitySpec->GetDynamicSpecSourceTags().AddTag(Tags.Abilities_Status_Equipped);
			}

			AssignSlotToAbility(*AbilitySpec, Slot);
			MarkAbilitySpecDirty(*AbilitySpec);
		}
		
		ClientEquipAbility(AbilityTag, Tags.Abilities_Status_Equipped, Slot, PrevSlot);
	}
}

void UDntAbilitySystemComponent::ClientEquipAbility_Implementation(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& Slot, const FGameplayTag& PreviousSlot)
{
	AbilityEquipped.Broadcast(AbilityTag, Status, Slot, PreviousSlot);
}

void UDntAbilitySystemComponent::ClientUpdateAbilityStatus_Implementation(const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 AbilityLevel)
{
	AbilityStatusChanged.Broadcast(AbilityTag, StatusTag, AbilityLevel);
}

void UDntAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handle)
{
	FGameplayTagContainer TagContainer; Spec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);
}

void UDntAbilitySystemComponent::MulticastActivatePassiveEffect_Implementation(const FGameplayTag& AbilityTag, bool bActivate)
{
	ActivatePassiveEffect.Broadcast(AbilityTag, bActivate);
}

/* =========================================================================
 * 8. Utility (通用工具)
 * ========================================================================= */

void UDntAbilitySystemComponent::ForEachAbility(const FForEachAbility& Delegate)
{
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!Delegate.ExecuteIfBound(AbilitySpec))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to execute delegate in %hs"), __FUNCTION__);
		}
	}
}

bool UDntAbilitySystemComponent::IsPassiveAbility(const FGameplayAbilitySpec& Spec) const
{
	const UAbilityInfo* AbilityInfo = UDntAbilitySystemLibrary::GetAbilityInfo(GetAvatarActor());
	const FGameplayTag AbilityTag = UDntAbilitySystemComponent::GetAbilityTagFromSpec(Spec);
	const FDntAbilityInfo& Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
	return Info.AbilityType.MatchesTagExact(FDntGameplayTags::Get().Abilities_Type_Passive);
}