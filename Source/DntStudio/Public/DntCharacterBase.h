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
	// Sets default values for this character's properties
	ADntCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
