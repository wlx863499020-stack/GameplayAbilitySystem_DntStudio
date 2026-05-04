 // DntStudio

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttributeInfo.generated.h"

 USTRUCT(BlueprintType)
 struct FDntAttributeInfo
 {
	 GENERATED_BODY()
	 
 	UPROPERTY(EditAnywhere, BlueprintReadOnly)
 	FGameplayTag AttributeTag = FGameplayTag();
 	
 	UPROPERTY(EditAnywhere, BlueprintReadOnly)
 	FText AttributeName = FText();
 	
 	UPROPERTY(EditAnywhere, BlueprintReadOnly)
 	FText AttributeDescription = FText();
 	
 	UPROPERTY(BlueprintReadOnly)
 	float AttributeValue = 0.f;
 	
 	
 };
/**
 * 
 */
UCLASS()
class DNTSTUDIO_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	FDntAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FDntAttributeInfo> AttributeInformation;
	
};
