// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DntProjectile.generated.h"

UCLASS()
class DNTSTUDIO_API ADntProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADntProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
