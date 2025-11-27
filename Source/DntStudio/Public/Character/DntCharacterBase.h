// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DntCharacterBase.generated.h"

UCLASS()
class DNTSTUDIO_API ADntCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ADntCharacterBase();

protected:
	virtual void BeginPlay() override;


};
