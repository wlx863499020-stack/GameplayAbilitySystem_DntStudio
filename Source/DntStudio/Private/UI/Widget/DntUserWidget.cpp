// DntStudio


#include "UI/Widget/DntUserWidget.h"

void UDntUserWidget::SetWidgetController(UObject* InWidgetController)
{
    WidgetController = InWidgetController;
	WidgetControllerSet();
}
