// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "DntDamageGameplayAbility.h"
#include "DntProjectileSpell.generated.h"

class ADntProjectile;
class UGameplayEffect;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class DNTSTUDIO_API UDntProjectileSpell : public UDntDamageGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo,const FGameplayAbilityActivationInfo activationInfo,const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	virtual void SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride, AActor* HomingTarget = nullptr
	);
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<ADntProjectile> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly)
	int32 NumProjectiles = 5;
	
	
};
