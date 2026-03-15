// DntStudio


#include "DntGameplayTags.h"
#include "GameplayTagsManager.h"


FDntGameplayTags FDntGameplayTags::GameplayTags;

void FDntGameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString ("Reduces damage taken,improves Block Chance"));
}


