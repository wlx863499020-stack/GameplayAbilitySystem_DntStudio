// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "Character/DntCharacterBase.h"
#include "DntCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DNTSTUDIO_API ADntCharacter : public ADntCharacterBase
{
	GENERATED_BODY()
	public:
	ADntCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	private:
	virtual void InitAbilityActorInfo() override;
};
