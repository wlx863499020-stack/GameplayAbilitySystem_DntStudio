	// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AttributeSet.h" 
#include "UI/WidgetController/DntWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FDntAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FDntAttributeInfo&, Info);
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class DNTSTUDIO_API UAttributeMenuWidgetController : public UDntWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallBacksToDependencies() override;
	virtual void BroadcastInitialValues() override;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;
	
	private:
	
	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};
