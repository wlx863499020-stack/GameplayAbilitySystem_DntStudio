// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/DntGameplayAbility.h"
#include "DntSummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class DNTSTUDIO_API UDntSummonAbility : public UDntGameplayAbility
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations();
	
	UFUNCTION(BlueprintPure, Category = "Summoning")
	TSubclassOf<APawn> GetRandomMinionClass();	 
	
	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	int32 NumMinions = 5;
	
	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	TArray<TSubclassOf<APawn>> MinionsClasses;
	
	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float MinSpawnDistance = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float MaxSpawnDistance = 250.f;

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float SpawnSpread = 90.f;
	
	
	
};
