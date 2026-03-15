// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DntUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DNTSTUDIO_API UDntUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
    void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
