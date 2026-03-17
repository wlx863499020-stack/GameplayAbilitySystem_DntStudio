// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DntHUD.generated.h"

class UAttributeMenuWidgetController;
class UAttributeSet;
class UAbilitySystemComponent;
class UOverlayWidgetController;
class UDntUserWidget;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class DNTSTUDIO_API ADntHUD : public AHUD
{
	GENERATED_BODY()
public:
	

	
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
	
	void InitOverlay(APlayerController* PC,APlayerState* PS,UAbilitySystemComponent* ASC, UAttributeSet* AS);
	


protected:
	
private:
	UPROPERTY()
	TObjectPtr<UDntUserWidget> OverlayWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDntUserWidget> OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
	
};
