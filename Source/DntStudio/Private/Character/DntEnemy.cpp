// DntStudio


#include "Character/DntEnemy.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/DntAbilitySystemComponent.h"
#include "AbilitySystem/DntAbilitySystemLibrary.h"
#include "AbilitySystem/DntAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "DntStudio/DntStudio.h"
#include "UI/Widget/DntUserWidget.h"
#include "DntGameplayTags.h"
#include "AI/DntAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ADntEnemy::ADntEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	
	AbilitySystemComponent = CreateDefaultSubobject<UDntAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	AttributeSet = CreateDefaultSubobject<UDntAttributeSet>("AttributeSet");
	
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void ADntEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (!HasAuthority()) return;
	DntAIController = Cast<ADntAIController>(NewController);	
	DntAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	DntAIController->RunBehaviorTree(BehaviorTree);
	DntAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	DntAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"),CharacterClass != ECharacterClass::Warrior); 
	
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

int32 ADntEnemy::GetPlayerLevel_Implementation()
{
	return Level;
}

void ADntEnemy::Die(const FVector& DeathImpulse)
{
	SetLifeSpan(LifeSpan);
	if (AIControllerClass)DntAIController->GetBlackboardComponent()->SetValueAsBool(FName("Dead"), true);
	Super::Die(DeathImpulse);
}

void ADntEnemy::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* ADntEnemy::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}


void ADntEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	InitAbilityActorInfo();
	if (HasAuthority())
	{
		UDntAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass);
	}
	
	
	
	if (UDntUserWidget* DntUserWidget = Cast<UDntUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		DntUserWidget->SetWidgetController(this);
	}
	
	
	if (const UDntAttributeSet* DntAS = Cast<UDntAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DntAS->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}	
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DntAS->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}	
		);

		AbilitySystemComponent->RegisterGameplayTagEvent(FDntGameplayTags::Get().Effect_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
		this ,
		&ADntEnemy::HitReactTagChanged
		);
		
		OnHealthChanged.Broadcast(DntAS->GetHealth());
		OnMaxHealthChanged.Broadcast(DntAS->GetMaxHealth());
	}

}

void ADntEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	if (DntAIController && DntAIController->GetBlackboardComponent())
	{
		DntAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
	}
}


void ADntEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	Cast<UDntAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	
	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
	OnAscRegistered.Broadcast(AbilitySystemComponent);
	
}

void ADntEnemy::InitializeDefaultAttributes() const
{
	UDntAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass,Level,AbilitySystemComponent);
}
