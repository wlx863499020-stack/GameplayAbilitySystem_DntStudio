// DntStudio

#include "AbilitySystem/DntAbilitySystemLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "DntAbilityTypes.h"
#include "DntGameplayTags.h"
#include "Engine/OverlapResult.h"
#include "Game/DntGameModeBase.h"
//#include "Game/LoadScreenSaveGame.h" // [已解封] 用于读取存档数据
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DntPlayerState.h"
#include "UI/HUD/DntHUD.h"
#include "UI/WidgetController/DntWidgetController.h"

/* =========================================================================
 * 1. UI Controller Factory (UI控制器工厂)
 * ========================================================================= */

bool UDntAbilitySystemLibrary::MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, ADntHUD*& OutDntHUD)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		OutDntHUD = Cast<ADntHUD>(PC->GetHUD());
		if (OutDntHUD)
		{
			ADntPlayerState* PS = PC->GetPlayerState<ADntPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			OutWCParams.AttributeSet = AS;                                                // 绑定属性集
			OutWCParams.AbilitySystemComponent = ASC;                                     // 绑定ASC
			OutWCParams.PlayerState = PS;                                                 // 绑定玩家状态
			OutWCParams.PlayerController = PC;                                            // 绑定控制器
			return true;
		}
	}
	return false;
}

UOverlayWidgetController* UDntAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams; ADntHUD* DntHUD = nullptr;
	return MakeWidgetControllerParams(WorldContextObject, WCParams, DntHUD) ? DntHUD->GetOverlayWidgetController(WCParams) : nullptr;
}

UAttributeMenuWidgetController* UDntAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams; ADntHUD* DntHUD = nullptr;
	return MakeWidgetControllerParams(WorldContextObject, WCParams, DntHUD) ? DntHUD->GetAttributeMenuWidgetController(WCParams) : nullptr;
}

USpellMenuWidgetController* UDntAbilitySystemLibrary::GetSpellMenuWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams; ADntHUD* DntHUD = nullptr;
	return MakeWidgetControllerParams(WorldContextObject, WCParams, DntHUD) ? DntHUD->GetSpellMenuWidgetController(WCParams) : nullptr;
}

/* =========================================================================
 * 2. Ability System Class Defaults (初始化)
 * ========================================================================= */

void UDntAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();
	UCharacterClassInfo* ClassInfo = GetCharacterClassInfo(WorldContextObject);	
	FCharacterClassDefaultInfo DefaultInfo = ClassInfo->GetClassDefaultInfo(CharacterClass);
	
	FGameplayEffectContextHandle PrimaryCtx = ASC->MakeEffectContext();
	PrimaryCtx.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimarySpec = ASC->MakeOutgoingSpec(DefaultInfo.PrimaryAttributes, Level, PrimaryCtx);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimarySpec.Data.Get());                           // 初始化核心五维

	FGameplayEffectContextHandle SecondaryCtx = ASC->MakeEffectContext();
	SecondaryCtx.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondarySpec = ASC->MakeOutgoingSpec(ClassInfo->SecondaryAttributes, Level, SecondaryCtx);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondarySpec.Data.Get());                         // 初始化LoL衍生

	FGameplayEffectContextHandle VitalCtx = ASC->MakeEffectContext();
	VitalCtx.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalSpec = ASC->MakeOutgoingSpec(ClassInfo->VitalAttributes, Level, VitalCtx);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalSpec.Data.Get());                             // 填满血蓝
}

/*
void UDntAbilitySystemLibrary::InitializeDefaultAttributesFromSaveData(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ULoadScreenSaveGame* SaveGame)
{
	UCharacterClassInfo* ClassInfo = GetCharacterClassInfo(WorldContextObject); if (!ClassInfo) return;
	const FDntGameplayTags& Tags = FDntGameplayTags::Get(); const AActor* AvatarActor = ASC->GetAvatarActor();

	FGameplayEffectContextHandle PrimaryCtx = ASC->MakeEffectContext(); PrimaryCtx.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimarySpec = ASC->MakeOutgoingSpec(ClassInfo->PrimaryAttributes_SetByCaller, 1.f, PrimaryCtx);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(PrimarySpec, Tags.Attributes_Primary_Strength, SaveGame->Strength);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(PrimarySpec, Tags.Attributes_Primary_Intelligence, SaveGame->Intelligence);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(PrimarySpec, Tags.Attributes_Primary_Resilience, SaveGame->Resilience);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(PrimarySpec, Tags.Attributes_Primary_Vigor, SaveGame->Vigor);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimarySpec.Data.Get());                           // 覆盖核心属性

	FGameplayEffectContextHandle SecondaryCtx = ASC->MakeEffectContext(); SecondaryCtx.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondarySpec = ASC->MakeOutgoingSpec(ClassInfo->SecondaryAttributes_Infinite, 1.f, SecondaryCtx);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondarySpec.Data.Get());                         // 覆盖次级属性

	FGameplayEffectContextHandle VitalCtx = ASC->MakeEffectContext(); VitalCtx.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalSpec = ASC->MakeOutgoingSpec(ClassInfo->VitalAttributes, 1.f, VitalCtx);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalSpec.Data.Get());                             // 覆盖生存属性
}
*/
void UDntAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass)
{
	UCharacterClassInfo* ClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (!ClassInfo) return;
	for (TSubclassOf<UGameplayAbility> AbilityClass : ClassInfo->CommonAbilities)
	{
		ASC->GiveAbility(FGameplayAbilitySpec(AbilityClass, 1));
	}
	const FCharacterClassDefaultInfo& DefaultInfo = ClassInfo->GetClassDefaultInfo(CharacterClass);
	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.StartupAbilities)
	{
		if (ASC->GetAvatarActor()->Implements<UCombatInterface>())
		{
			ASC->GiveAbility(FGameplayAbilitySpec(AbilityClass, ICombatInterface::Execute_GetPlayerLevel(ASC->GetAvatarActor())));
		}
	}
}

UCharacterClassInfo* UDntAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	const ADntGameModeBase* GM = Cast<ADntGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	return GM ? GM->CharacterClassInfo : nullptr;
}

UAbilityInfo* UDntAbilitySystemLibrary::GetAbilityInfo(const UObject* WorldContextObject)
{
	const ADntGameModeBase* GM = Cast<ADntGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	return GM ? GM->AbilityInfo : nullptr;
}

// [已补全] 战利品掉落表读取逻辑
/*ULootTiers* UDntAbilitySystemLibrary::GetLootTiers(const UObject* WorldContextObject)
{
	const ADntGameModeBase* GM = Cast<ADntGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	return GM ? GM->LootTiers : nullptr;
}
*/
/* =========================================================================
 * 3. Effect Context Getters (状态读取)
 * ========================================================================= */

EDntDamageType UDntAbilitySystemLibrary::GetDamageType(const FGameplayEffectContextHandle& Handle)
{
	if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(Handle.Get())) return C->GetDamageType();
	return EDntDamageType::None;                                                          // 读:LoL路径枚举
}

FGameplayTag UDntAbilitySystemLibrary::GetDamageTypeTag(const FGameplayEffectContextHandle& Handle)
{
	if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(Handle.Get()))
	{
		if (C->GetDamageTypeTag().IsValid()) // [修复] 检查智能指针有效性
		{
			return *C->GetDamageTypeTag();   // [修复] 加 * 解引用，返回 FGameplayTag
		}
	}
	return FGameplayTag();
}

bool UDntAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsBlockedHit(); return false; }
bool UDntAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsCriticalHit(); return false; }
bool UDntAbilitySystemLibrary::IsDodgedHit(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsDodgedHit(); return false; }
bool UDntAbilitySystemLibrary::IsInvulnerableHit(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsInvulnerableHit(); return false; }
bool UDntAbilitySystemLibrary::IsShieldBroken(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsShieldBroken(); return false; }
bool UDntAbilitySystemLibrary::IsSuccessfulDebuff(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsSuccessfulDebuff(); return false; }
float UDntAbilitySystemLibrary::GetDebuffDamage(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->GetDebuffDamage(); return 0.f; }
float UDntAbilitySystemLibrary::GetDebuffDuration(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->GetDebuffDuration(); return 0.f; }
float UDntAbilitySystemLibrary::GetDebuffFrequency(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->GetDebuffFrequency(); return 0.f; }
bool UDntAbilitySystemLibrary::IsBasicAttack(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsBasicAttack(); return false; }
bool UDntAbilitySystemLibrary::IsAbilityDamage(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsAbilityDamage(); return false; }
bool UDntAbilitySystemLibrary::IsPeriodicDamage(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsPeriodicDamage(); return false; }
bool UDntAbilitySystemLibrary::IsAoEDamage(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsAoEDamage(); return false; }
bool UDntAbilitySystemLibrary::IsPetDamage(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsPetDamage(); return false; }
bool UDntAbilitySystemLibrary::IsReflectedDamage(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsReflectedDamage(); return false; }
bool UDntAbilitySystemLibrary::IsPhantomHit(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsPhantomHit(); return false; }
bool UDntAbilitySystemLibrary::IsExecuteHit(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsExecuteHit(); return false; }
bool UDntAbilitySystemLibrary::HasLifesteal(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->HasLifesteal(); return false; }
bool UDntAbilitySystemLibrary::IsInterruptHit(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsInterruptHit(); return false; }
bool UDntAbilitySystemLibrary::IsHeal(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsHeal(); return false; }
bool UDntAbilitySystemLibrary::IsShieldApplication(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsShieldApplication(); return false; }
bool UDntAbilitySystemLibrary::IsBackstab(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsBackstab(); return false; }
bool UDntAbilitySystemLibrary::IsStealthHit(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsStealthHit(); return false; }
bool UDntAbilitySystemLibrary::IsTurretDamage(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsTurretDamage(); return false; }
bool UDntAbilitySystemLibrary::IsFountainDamage(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsFountainDamage(); return false; }
bool UDntAbilitySystemLibrary::BypassesShields(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->BypassesShields(); return false; }
bool UDntAbilitySystemLibrary::IsFatalHit(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsFatalHit(); return false; }
bool UDntAbilitySystemLibrary::IsNonLethal(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsNonLethal(); return false; }
float UDntAbilitySystemLibrary::GetTypeMultiplier(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->GetTypeMultiplier(); return 1.0f; }
FVector UDntAbilitySystemLibrary::GetDeathImpulse(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->GetDeathImpulse(); return FVector::ZeroVector; }
FVector UDntAbilitySystemLibrary::GetKnockbackForce(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->GetKnockbackForce(); return FVector::ZeroVector; }
bool UDntAbilitySystemLibrary::IsRadialDamage(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->IsRadialDamage(); return false; }
float UDntAbilitySystemLibrary::GetRadialDamageInnerRadius(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->GetRadialDamageInnerRadius(); return 0.f; }
float UDntAbilitySystemLibrary::GetRadialDamageOuterRadius(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->GetRadialDamageOuterRadius(); return 0.f; }
FVector UDntAbilitySystemLibrary::GetRadialDamageOrigin(const FGameplayEffectContextHandle& H) { if (const FDntGameplayEffectContext* C = static_cast<const FDntGameplayEffectContext*>(H.Get())) return C->GetRadialDamageOrigin(); return FVector::ZeroVector; }

/* =========================================================================
 * 4. Effect Context Setters (状态写入)
 * ========================================================================= */

void UDntAbilitySystemLibrary::SetDamageType(FGameplayEffectContextHandle& H, EDntDamageType InT) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetDamageType(InT); }
void UDntAbilitySystemLibrary::SetDamageTypeTag(FGameplayEffectContextHandle& H, const FGameplayTag& InT) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetDamageTypeTag(InT); }
void UDntAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsBlockedHit(bIn); }
void UDntAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsCriticalHit(bIn); }
void UDntAbilitySystemLibrary::SetIsSuccessfulDebuff(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsSuccessfulDebuff(bIn); }
void UDntAbilitySystemLibrary::SetDebuffDamage(FGameplayEffectContextHandle& H, float InV) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetDebuffDamage(InV); }
void UDntAbilitySystemLibrary::SetDebuffDuration(FGameplayEffectContextHandle& H, float InV) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetDebuffDuration(InV); }
void UDntAbilitySystemLibrary::SetDebuffFrequency(FGameplayEffectContextHandle& H, float InV) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetDebuffFrequency(InV); }
void UDntAbilitySystemLibrary::SetDeathImpulse(FGameplayEffectContextHandle& H, const FVector& InV) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetDeathImpulse(InV); }
void UDntAbilitySystemLibrary::SetKnockbackForce(FGameplayEffectContextHandle& H, const FVector& InV) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetKnockbackForce(InV); }
void UDntAbilitySystemLibrary::SetIsRadialDamage(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsRadialDamage(bIn); }
void UDntAbilitySystemLibrary::SetRadialDamageInnerRadius(FGameplayEffectContextHandle& H, float InV) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetRadialDamageInnerRadius(InV); }
void UDntAbilitySystemLibrary::SetRadialDamageOuterRadius(FGameplayEffectContextHandle& H, float InV) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetRadialDamageOuterRadius(InV); }
void UDntAbilitySystemLibrary::SetRadialDamageOrigin(FGameplayEffectContextHandle& H, const FVector& InV) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetRadialDamageOrigin(InV); }
void UDntAbilitySystemLibrary::SetTypeMultiplier(FGameplayEffectContextHandle& H, float InV) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetTypeMultiplier(InV); }
void UDntAbilitySystemLibrary::SetIsDodgedHit(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsDodgedHit(bIn); }
void UDntAbilitySystemLibrary::SetIsInvulnerableHit(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsInvulnerableHit(bIn); }
void UDntAbilitySystemLibrary::SetShieldBroken(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetShieldBroken(bIn); }
void UDntAbilitySystemLibrary::SetIsBasicAttack(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsBasicAttack(bIn); }
void UDntAbilitySystemLibrary::SetIsAbilityDamage(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsAbilityDamage(bIn); }
void UDntAbilitySystemLibrary::SetIsPeriodicDamage(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsPeriodicDamage(bIn); }
void UDntAbilitySystemLibrary::SetIsAoEDamage(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsAoEDamage(bIn); }
void UDntAbilitySystemLibrary::SetIsPetDamage(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsPetDamage(bIn); }
void UDntAbilitySystemLibrary::SetIsReflectedDamage(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsReflectedDamage(bIn); }
void UDntAbilitySystemLibrary::SetHasLifesteal(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetHasLifesteal(bIn); }
void UDntAbilitySystemLibrary::SetIsPhantomHit(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsPhantomHit(bIn); }
void UDntAbilitySystemLibrary::SetIsExecuteHit(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsExecuteHit(bIn); }
void UDntAbilitySystemLibrary::SetIsInterruptHit(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsInterruptHit(bIn); }
void UDntAbilitySystemLibrary::SetIsHeal(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsHeal(bIn); }
void UDntAbilitySystemLibrary::SetIsShieldApplication(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsShieldApplication(bIn); }
void UDntAbilitySystemLibrary::SetIsBackstab(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsBackstab(bIn); }
void UDntAbilitySystemLibrary::SetIsStealthHit(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsStealthHit(bIn); }
void UDntAbilitySystemLibrary::SetIsTurretDamage(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsTurretDamage(bIn); }
void UDntAbilitySystemLibrary::SetIsFountainDamage(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsFountainDamage(bIn); }
void UDntAbilitySystemLibrary::SetBypassesShields(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetBypassesShields(bIn); }
void UDntAbilitySystemLibrary::SetIsFatalHit(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsFatalHit(bIn); }
void UDntAbilitySystemLibrary::SetIsNonLethal(FGameplayEffectContextHandle& H, bool bIn) { if (FDntGameplayEffectContext* C = static_cast<FDntGameplayEffectContext*>(H.Get())) C->SetIsNonLethal(bIn); }

/* =========================================================================
 * 5. Gameplay Mechanics & Algorithms (机制与算法)
 * ========================================================================= */

void UDntAbilitySystemLibrary::GetLivePlayersWithinRadius(const UObject* WCO, TArray<AActor*>& OutActors, const TArray<AActor*>& IgnoreActors, float Radius, const FVector& Origin)
{
	FCollisionQueryParams Params; Params.AddIgnoredActors(IgnoreActors);
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WCO, EGetWorldErrorMode::LogAndReturnNull))
	{
		TArray<FOverlapResult> Overlaps;
		World->OverlapMultiByObjectType(Overlaps, Origin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), Params);
		for (FOverlapResult& O : Overlaps) { if (O.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(O.GetActor())) OutActors.AddUnique(O.GetActor()); }
	}
}

void UDntAbilitySystemLibrary::GetClosestTargets(int32 MaxTargets, const TArray<AActor*>& Actors, TArray<AActor*>& OutTargets, const FVector& Origin)
{
	if (Actors.Num() <= MaxTargets) { OutTargets = Actors; return; }
	TArray<AActor*> ActorsToCheck = Actors; int32 FoundCount = 0;
	while (FoundCount < MaxTargets && ActorsToCheck.Num() > 0)
	{
		double MinDist = TNumericLimits<double>::Max(); AActor* Closest = nullptr;
		for (AActor* A : ActorsToCheck) { const double Dist = (A->GetActorLocation() - Origin).Size(); if (Dist < MinDist) { MinDist = Dist; Closest = A; } }
		ActorsToCheck.Remove(Closest); OutTargets.AddUnique(Closest); ++FoundCount;
	}
}

bool UDntAbilitySystemLibrary::IsNotFriend(AActor* A1, AActor* A2)
{
	const bool bBothPlayers = A1->ActorHasTag(FName("Player")) && A2->ActorHasTag(FName("Player"));
	const bool bBothEnemies = A1->ActorHasTag(FName("Enemy")) && A2->ActorHasTag(FName("Enemy"));
	return !(bBothPlayers || bBothEnemies);
}

FGameplayEffectContextHandle UDntAbilitySystemLibrary::ApplyDamageEffect(const FDamageEffectParams& Params)
{
	const FDntGameplayTags& Tags = FDntGameplayTags::Get();
	FGameplayEffectContextHandle Handle = Params.SourceAbilitySystemComponent->MakeEffectContext();
	Handle.AddSourceObject(Params.SourceAbilitySystemComponent->GetAvatarActor());
	SetDeathImpulse(Handle, Params.DeathImpulse); SetKnockbackForce(Handle, Params.KnockbackForce);
	SetIsRadialDamage(Handle, Params.bIsRadialDamage); SetRadialDamageInnerRadius(Handle, Params.RadialDamageInnerRadius);
	SetRadialDamageOuterRadius(Handle, Params.RadialDamageOuterRadius); SetRadialDamageOrigin(Handle, Params.RadialDamageOrigin);
	SetIsBasicAttack(Handle, Params.bIsBasicAttack);
	const FGameplayEffectSpecHandle Spec = Params.SourceAbilitySystemComponent->MakeOutgoingSpec(Params.DamageGameplayEffectClass, Params.AbilityLevel, Handle);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(Spec, Params.DamageType, Params.BaseDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(Spec, Tags.Debuff_Chance, Params.DebuffChance);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(Spec, Tags.Debuff_Damage, Params.DebuffDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(Spec, Tags.Debuff_Duration, Params.DebuffDuration);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(Spec, Tags.Debuff_Frequency, Params.DebuffFrequency);
	Params.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
	return Handle;
}

TArray<FRotator> UDntAbilitySystemLibrary::EvenlySpacedRotators(const FVector& Forward, const FVector& Axis, float Spread, int32 Num)
{
	TArray<FRotator> Rots; const FVector LeftOfSpread = Forward.RotateAngleAxis(-Spread / 2.f, Axis);
	if (Num > 1) { const float Delta = Spread / (Num - 1); for (int32 i = 0; i < Num; i++) Rots.Add(LeftOfSpread.RotateAngleAxis(Delta * i, FVector::UpVector).Rotation()); }
	else Rots.Add(Forward.Rotation()); return Rots;
}

TArray<FVector> UDntAbilitySystemLibrary::EvenlyRotatedVectors(const FVector& Forward, const FVector& Axis, float Spread, int32 Num)
{
	TArray<FVector> Vecs; const FVector LeftOfSpread = Forward.RotateAngleAxis(-Spread / 2.f, Axis);
	if (Num > 1) { const float Delta = Spread / (Num - 1); for (int32 i = 0; i < Num; i++) Vecs.Add(LeftOfSpread.RotateAngleAxis(Delta * i, FVector::UpVector)); }
	else Vecs.Add(Forward); return Vecs;
}

int32 UDntAbilitySystemLibrary::GetXPRewardForClassAndLevel(const UObject* WCO, ECharacterClass CC, int32 Lv)
{
	UCharacterClassInfo* ClassInfo = GetCharacterClassInfo(WCO);
	return ClassInfo ? static_cast<int32>(ClassInfo->GetClassDefaultInfo(CC).XPReward.GetValueAtLevel(Lv)) : 0;
}

/* =========================================================================
 * 6. Damage Effect Params Helpers (设置助手)
 * ========================================================================= */

void UDntAbilitySystemLibrary::SetIsRadialDamageEffectParam(FDamageEffectParams& Params, bool bIsR, float Inner, float Outer, FVector Origin)
{
	Params.bIsRadialDamage = bIsR; Params.RadialDamageInnerRadius = Inner; Params.RadialDamageOuterRadius = Outer; Params.RadialDamageOrigin = Origin;
}

void UDntAbilitySystemLibrary::SetKnockbackDirection(FDamageEffectParams& Params, FVector Dir, float Mag)
{
	Dir.Normalize(); Params.KnockbackForce = Dir * (Mag == 0.f ? Params.KnockbackForceMagnitude : Mag);
}

void UDntAbilitySystemLibrary::SetDeathImpulseDirection(FDamageEffectParams& Params, FVector Dir, float Mag)
{
	Dir.Normalize(); Params.DeathImpulse = Dir * (Mag == 0.f ? Params.DeathImpulseMagnitude : Mag);
}

void UDntAbilitySystemLibrary::SetTargetEffectParamsASC(FDamageEffectParams& Params, UAbilitySystemComponent* ASC)
{
	Params.TargetAbilitySystemComponent = ASC;
}