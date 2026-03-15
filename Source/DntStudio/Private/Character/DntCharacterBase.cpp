 // DntStudio


#include "Character/DntCharacterBase.h"
#include "AbilitySystemComponent.h"

ADntCharacterBase::ADntCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon ->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon ->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

 UAbilitySystemComponent* ADntCharacterBase::GetAbilitySystemComponent() const
 {
	return AbilitySystemComponent;
 }

 void ADntCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

 void ADntCharacterBase::InitAbilityActorInfo()
 {
 }

 void ADntCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
 {
	check(IsValid(GetAbilitySystemComponent()))
	check(GameplayEffectClass)
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle= GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass,Level,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
 }

 void ADntCharacterBase::InitializeDefaultAttributes() const
 {
	ApplyEffectToSelf(DefualtPrimaryAttributes,1.f);
	ApplyEffectToSelf(DefualtSecondaryAttributes,1.f);
	ApplyEffectToSelf(DefualtVitalAttributes,1.f);
 }


