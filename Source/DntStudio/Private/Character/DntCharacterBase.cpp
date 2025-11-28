 // DntStudio


#include "Character/DntCharacterBase.h"

ADntCharacterBase::ADntCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon ->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon ->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ADntCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

