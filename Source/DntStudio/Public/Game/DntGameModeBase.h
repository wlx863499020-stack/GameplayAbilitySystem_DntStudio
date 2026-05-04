// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DntGameModeBase.generated.h"


class UAbilityInfo;
class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class DNTSTUDIO_API ADntGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo>CharacterClassInfo;
	
	UPROPERTY(EditDefaultsOnly, Category = "Ability Info")
	TObjectPtr<UAbilityInfo> AbilityInfo;
};
