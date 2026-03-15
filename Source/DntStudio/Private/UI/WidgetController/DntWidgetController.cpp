// DntStudio


#include "UI/WidgetController/DntWidgetController.h"

void UDntWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UDntWidgetController::BroadcastInitialValues()
{
	
}

void UDntWidgetController::BindCallBacksToDependencies()
{
	
}
