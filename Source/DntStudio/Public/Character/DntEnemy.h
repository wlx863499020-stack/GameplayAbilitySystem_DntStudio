// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "Character/DntCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "DntEnemy.generated.h"

/**
 * 
 */
UCLASS()
class DNTSTUDIO_API ADntEnemy : public ADntCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()
public:
	ADntEnemy();
	
	/**Enemy Interface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/**end Enemy Interface */
	/*Combat Interface*/
	virtual int32 GetPlayerLevel() override; 
	/*end Combat Interface*/
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Character Class Defults");
	int32 Level = 1;
	
};
