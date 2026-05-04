// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "Character/DntCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "DntEnemy.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class ADntAIController;
/**
 * 
 */
UCLASS()
class DNTSTUDIO_API ADntEnemy : public ADntCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()
public:
	ADntEnemy();
	virtual void PossessedBy(AController* NewController) override;
	
	/**Enemy Interface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/**end Enemy Interface */
	
	/*Combat Interface*/
	virtual int32 GetPlayerLevel_Implementation() override; 
	virtual void Die(const FVector& DeathImpulse) override;
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;
	/*end Combat Interface*/
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	
	UPROPERTY(BlueprintReadOnly,Category="Combat")
	bool bHitReacting = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Combat")
	float BaseWalkSpeed = 250.f;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Combat")
	float LifeSpan = 5.f;
	
	UPROPERTY(BlueprintReadWrite,Category="Combat")
	TObjectPtr<AActor> CombatTarget;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;
	
	UPROPERTY(EditAnywhere, Category = "Character Class Defults");
	int32 Level = 1;
	
	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	TObjectPtr<UWidgetComponent> HealthBar ;
	
	UPROPERTY(EditAnywhere, Category = "AI");
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY()
	TObjectPtr<ADntAIController> DntAIController;
	
};
