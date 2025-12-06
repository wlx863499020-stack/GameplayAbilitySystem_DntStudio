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
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
};
