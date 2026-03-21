// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/DntGameplayAbility.h"
#include "DntProjectileSpell.generated.h"

class ADntProjectile;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class DNTSTUDIO_API UDntProjectileSpell : public UDntGameplayAbility
{
	GENERATED_BODY()

	protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo,const FGameplayAbilityActivationInfo activationInfo,const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION(BlueprintCallable,Category="Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<ADntProjectile> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamegeEffectClass; 
};
