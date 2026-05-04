// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DntAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class DNTSTUDIO_API ADntAIController : public AAIController
{
	GENERATED_BODY()
public:
	ADntAIController();
	
protected:
	
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
	
};
