// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */

struct FDntGameplayTags
{
public:
	static const FDntGameplayTags& Get(){return GameplayTags;}
	static void InitializeNativeGameplayTags();
	
protected:
	
private:
	static FDntGameplayTags GameplayTags;
};
