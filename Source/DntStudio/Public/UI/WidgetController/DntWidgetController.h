// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DntWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChangedSignature, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityInfoSignature, const FDntAbilityInfo&, Info);

class UAttributeSet;
class UAbilitySystemComponent;
class ADntPlayerController;
class ADntPlayerState;
class UDntAbilitySystemComponent;
class UDntAttributeSet;
class UAbilityInfo;

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
	
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies();
	
	UPROPERTY(BlueprintAssignable,Category="GAS|Messages")
	FAbilityInfoSignature AbilityInfoDelegate;
	
	void BroadcastAbilityInfo();
protected:
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Widget Data")
	TObjectPtr<UAbilityInfo> AbilityInfo;
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController)")
	TObjectPtr<APlayerController> PlayerController;
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController)")
	TObjectPtr<APlayerState> PlayerState;
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController)")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController)")
	TObjectPtr<UAttributeSet> AttributeSet; 
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController)")
	TObjectPtr<ADntPlayerController> DntPlayerController;
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController)")
	TObjectPtr<ADntPlayerState> DntPlayerState;
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController)")
	TObjectPtr<UDntAbilitySystemComponent> DntAbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController)")
	TObjectPtr<UDntAttributeSet> DntAttributeSet; 
	
	ADntPlayerController* GetDntPC();
	ADntPlayerState* GetDntPS();
	UDntAbilitySystemComponent* GetDntASC();
	UDntAttributeSet* GetDntAS();
};
