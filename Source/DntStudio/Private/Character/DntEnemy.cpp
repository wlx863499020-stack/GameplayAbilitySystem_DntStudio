// DntStudio


#include "Character/DntEnemy.h"

#include "EditorDirectories.h"
#include "AbilitySystem/DntAbilitySystemComponent.h"
#include "AbilitySystem/DntAttributeSet.h"
#include "DntStudio/DntStudio.h"

ADntEnemy::ADntEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	
	AbilitySystemComponent = CreateDefaultSubobject<UDntAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UDntAttributeSet>("AttributeSet");
}

void ADntEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void ADntEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 ADntEnemy::GetPlayerLevel()
{
	return Level;
}

void ADntEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void ADntEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	Cast<UDntAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}
