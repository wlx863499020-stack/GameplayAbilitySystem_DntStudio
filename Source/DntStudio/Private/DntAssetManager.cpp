// DntStudio


#include "DntAssetManager.h"

#include "AbilitySystemComponent.h"
#include "DntGameplayTags.h"

UDntAssetManager& UDntAssetManager::Get()
{
	check(GEngine);
	
	UDntAssetManager* DntAssetManager =  Cast<UDntAssetManager>(GEngine->AssetManager);
	return * DntAssetManager;
}

void UDntAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FDntGameplayTags::InitializeNativeGameplayTags();
	//UAbilitySystemGlobals::Get().InitGlobalData();
}

