// DntStudio


#include "Actor/DntProjectile.h"

// Sets default values
ADntProjectile::ADntProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADntProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADntProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

