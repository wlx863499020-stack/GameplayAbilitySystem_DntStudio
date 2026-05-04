// DntStudio


#include "AbilitySystem/Abilities/DntProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/DntProjectile.h"
#include "Interaction/CombatInterface.h"
#include "DntStudio/Public/DntGameplayTags.h"
#include "GameFramework/ProjectileMovementComponent.h"


void UDntProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo activationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, activationInfo, TriggerEventData);
	
	
}

void UDntProjectileSpell::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	// 1. 获取生成位置
	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(),
		SocketTag);

	// 2. 计算基础旋转
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();

	// 3. 【核心改动】：应用 Pitch 覆盖 (解决法球贴地飞或飞天的问题)
	if (bOverridePitch)
	{
		Rotation.Pitch = PitchOverride;
	}

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());

	// 4. 延迟生成子弹
	ADntProjectile* Projectile = GetWorld()->SpawnActorDeferred<ADntProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	// 5. 传递伤害参数 (这里包含了你之前配置的 LoL 和 Pokemon 所有的 45 个属性)
	Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();

	// 6. 【核心改动】：配置追踪目标 (类似维鲁斯的 Q 或指向性技能)
	if (HomingTarget && HomingTarget->Implements<UCombatInterface>())
	{
		// 确保 Projectile 内部有公开的 ProjectileMovement 组件
		if (Projectile->ProjectileMovement)
		{
			Projectile->ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
		}
	}

	// 7. 完成生成
	Projectile->FinishSpawning(SpawnTransform);
}
