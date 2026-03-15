// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "DntPlayerState.generated.h"



class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class DNTSTUDIO_API ADntPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ADntPlayerState();
	virtual void GetLifetimeReplicatedProps (TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const{return AttributeSet;}
	
	FORCEINLINE int32 GetPlayerLevel() const{return Level;}
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	private:
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1;
	
	UFUNCTION()
	void OnRep_Level(int32 OldLevel) const;
	
};
