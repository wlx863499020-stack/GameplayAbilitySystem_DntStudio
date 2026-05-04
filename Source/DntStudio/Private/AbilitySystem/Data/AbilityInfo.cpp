// DntStudio


#include "AbilitySystem/Data/AbilityInfo.h"

#include "DntStudio/DntLogChannals.h"

FDntAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for (const FDntAbilityInfo& Info : AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogDnt, Error, TEXT("Can't find info for AbilityTag [%s] on AbilityInfo [%s]"), 
			*AbilityTag.ToString(), *GetNameSafe(this));
	}

	return FDntAbilityInfo();
}
