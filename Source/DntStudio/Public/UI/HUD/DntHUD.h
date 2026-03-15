// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DntHUD.generated.h"

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
	
	UPROPERTY()
	TObjectPtr<UDntUserWidget> OverlayWidget;
	
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	
	void InitOverlay(APlayerController* PC,APlayerState* PS,UAbilitySystemComponent* ASC, UAttributeSet* AS);
	


protected:
	
		private:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDntUserWidget> OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
};
