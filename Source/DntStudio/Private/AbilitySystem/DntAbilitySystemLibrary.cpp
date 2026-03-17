// DntStudio


#include "AbilitySystem/DntAbilitySystemLibrary.h"
#include "UI/WidgetController/DntWidgetController.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DntPlayerState.h"
#include "UI/HUD/DntHUD.h"

UOverlayWidgetController* UDntAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ADntHUD* DntHUD = Cast<ADntHUD>(PC->GetHUD()))
		{
			ADntPlayerState* PS = PC->GetPlayerState<ADntPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
			return DntHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UDntAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ADntHUD* DntHUD = Cast<ADntHUD>(PC->GetHUD()))
		{
			ADntPlayerState* PS = PC->GetPlayerState<ADntPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
			return DntHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
