// DntStudio


#include "DntAssetManager.h"
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
	
	UE_LOG(LogTemp, Warning, TEXT("====== DntAssetManager is Running! ======")); 
	
	FDntGameplayTags::InitializeNativeGameplayTags();
}

