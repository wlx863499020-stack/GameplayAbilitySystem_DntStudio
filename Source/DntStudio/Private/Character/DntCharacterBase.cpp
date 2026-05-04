 // DntStudio


#include "Character/DntCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "DntGameplayTags.h"
#include "AbilitySystem/DntAbilitySystemComponent.h"
#include "AbilitySystem/Debuff/DebuffNiagaraComponent.h"
#include "Components/CapsuleComponent.h"
#include "DntStudio/DntStudio.h"
#include "Kismet/GameplayStatics.h"

 ADntCharacterBase::ADntCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
 	
 	BurnDebuffComponent = CreateDefaultSubobject<UDebuffNiagaraComponent>("BurnDebuffComponent");
 	BurnDebuffComponent->SetupAttachment(GetRootComponent());
 	BurnDebuffComponent->DebuffTag = FDntGameplayTags::Get().Debuff_Physical;
 	
 	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
 	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
 	GetMesh()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
 	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile,ECR_Overlap);
 	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon ->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon ->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

 UAbilitySystemComponent* ADntCharacterBase::GetAbilitySystemComponent() const
 {
	return AbilitySystemComponent;
 }

 UAnimMontage* ADntCharacterBase::GetHitReactMontage_Implementation()
 {
	 return HitReactMontage;
 }

 void ADntCharacterBase::Die(const FVector& DeathImpulse)
 {
 	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld,true));
 	MulticastHandleDeath(DeathImpulse);
 }

 void ADntCharacterBase::MulticastHandleDeath_Implementation(const FVector& DeathImpulse)
 {
 	UGameplayStatics::PlaySoundAtLocation(this, DeathSound,GetActorLocation(),GetActorRotation());
 	
 	Weapon->SetSimulatePhysics(true);
 	Weapon->SetEnableGravity(true);
 	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
 	Weapon->AddImpulse(DeathImpulse * 0.1f, NAME_None,true);

 	GetMesh()->SetSimulatePhysics(true);
 	GetMesh()->SetEnableGravity(true);
 	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
 	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
 	GetMesh()->AddImpulse(DeathImpulse, NAME_None,true);

 	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
 	Dissolve();
 	bDead = true;
 	OnDeath.Broadcast(this);
 }

 void ADntCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

 FVector ADntCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
 {
 	const FDntGameplayTags& GameplayTags = FDntGameplayTags::Get();

 	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_Weapon) && IsValid(Weapon))
 	{
 		return Weapon->GetSocketLocation(WeaponTipSocketName);
 	}

 	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_LeftHand))
 	{
 		return GetMesh()->GetSocketLocation(LeftHandSocketName);
 	}

 	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_RightHand))
 	{
 		return GetMesh()->GetSocketLocation(RightHandSocketName);
 	}
 	
 	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_RightFoot))
 	{
 		return GetMesh()->GetSocketLocation(RightFootSocketName);
 	}
 	
 	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_LeftFoot))
 	{
 		return GetMesh()->GetSocketLocation(LeftFootSocketName);
 	}
 	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_RightKnee))
 	{
 		return GetMesh()->GetSocketLocation(RightKneeSocketName);
 	}
 	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_LeftKnee))
 	{
 		return GetMesh()->GetSocketLocation(LeftKneeSocketName);
 	}
 	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_RightElbow))
 	{
 		return GetMesh()->GetSocketLocation(RightElbowSocketName);
 	}
 	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_LeftElbow))
 	{
 		return GetMesh()->GetSocketLocation(LeftElbowSocketName);
 	}
 	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_Tail))
 	{
 		return GetMesh()->GetSocketLocation(TailSocketName);
 	}
 	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_Head))
 	{
 		return GetMesh()->GetSocketLocation(HeadSocketName);
 	}
 	return FVector();
 }

 bool ADntCharacterBase::IsDead_Implementation() const
 {
	 return bDead;
 }

 AActor* ADntCharacterBase::GetAvatar_Implementation()
 {
	 return this;
 }

 TArray<FTaggedMontage> ADntCharacterBase::GetAttackMontages_Implementation()
 {
	 return AttackMontages;
 }

 UNiagaraSystem* ADntCharacterBase::GetBloodEffect_Implementation()
 {
	 return BloodEffect;
 }

 FTaggedMontage ADntCharacterBase::GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag)
 {
 	for (FTaggedMontage TaggedMontage : AttackMontages)
 	{
 		if (TaggedMontage.MontageTag == MontageTag)
 		{
 			return TaggedMontage;
 		}
 	}

 	return FTaggedMontage();
 }

 int32 ADntCharacterBase::GetMinionsCount_Implementation()
 {
	 return MinionCount;
 }

 void ADntCharacterBase::IncremenetMinionCount_Implementation(int32 Amount)
 {
	 MinionCount += Amount;
 }

 ECharacterClass ADntCharacterBase::GetCharacterClass_Implementation()
 {
	 return CharacterClass;
 }

FOnAscRegistered& ADntCharacterBase::GetOnASCRegisteredDelegate()
 {
 	return OnAscRegistered;
 }

FOnDeath& ADntCharacterBase::GetOnDeathDelegate()
 {
 	return OnDeath;
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
	ApplyEffectToSelf(DefaultPrimaryAttributes,1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes,1.f);
	ApplyEffectToSelf(DefaultVitalAttributes,1.f);
 }

 void ADntCharacterBase::AddCharacterAbilities()
 {
	UDntAbilitySystemComponent* DntASC = CastChecked<UDntAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;
	
	DntASC->AddCharacterAbilities(StartupAbilities);
 	DntASC->AddCharacterPassiveAbilities(StartupPassiveAbilities);
 }

void ADntCharacterBase::Dissolve()
 {
 	if (IsValid(DissolveMaterialInstance))
 	{
 		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
 		GetMesh()->SetMaterial(0, DynamicMatInst);
 		StartDissolveTimeline(DynamicMatInst);
 	}

 	if (IsValid(WeaponDissolveMaterialInstance))
 	{
 		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
 		Weapon->SetMaterial(0, DynamicMatInst);
 		StartWeaponDissolveTimeline(DynamicMatInst);
 	}
 }


