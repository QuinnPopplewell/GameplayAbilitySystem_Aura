


#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"


UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
    if (OverlayWidgetController == nullptr)
    {
        OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
        OverlayWidgetController->SetWidgetControllerParams(WCParams);

        return OverlayWidgetController;
    }
    return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
    //If OverlayWidgetClass or OverlayWidgetControllerClass is null,
    //Crash with message logs
    checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
    checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));

    //Create the widget, 
    //then cast it to the overlay widget to get its functionality
    UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
    OverlayWidget = Cast<UAuraUserWidget>(Widget);

    //Construct a new set of widget controller params,
    //then construct a new Widget Controller if one doesn't exist,
    //then set the OverlayWidget's controller to it,
    //then add the widget to the viewport
    const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
    UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
    OverlayWidget->SetWidgetController(WidgetController);

    Widget->AddToViewport();
}
