// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DntWidgetController.generated.h"


class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
	FWidgetControllerParams(){}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS) 
	: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS)   {}
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TObjectPtr<APlayerController> PlayerController = nullptr;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TObjectPtr<APlayerState> PlayerState = nullptr;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;
	
};

/**
 * 
 */
UCLASS()
class DNTSTUDIO_API UDntWidgetController : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);
	virtual void BroadcastInitialValues();
	virtual void BindCallBacksToDependencies();
protected:
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController)")
	TObjectPtr<APlayerController> PlayerController;
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController)")
	TObjectPtr<APlayerState> PlayerState;
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController)")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController)")
	TObjectPtr<UAttributeSet> AttributeSet; 
};
