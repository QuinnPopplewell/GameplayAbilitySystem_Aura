


#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"


UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
    if (OverlayWidgetController == nullptr)
    {
        OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
        OverlayWidgetController->SetWidgetControllerParams(WCParams);
        OverlayWidgetController->BindCallbacksToDependencies();

    }
    return OverlayWidgetController;
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
    if (AttributeMenuWidgetController == nullptr)
    {
        AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
        AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
        AttributeMenuWidgetController->BindCallbacksToDependencies();

    }
    return AttributeMenuWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
    //If OverlayWidgetClass or OverlayWidgetControllerClass is null,
    //Crash with message logs
    checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
    checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));
    checkf(AttributeMenuWidgetControllerClass, TEXT("Attribute Menu Widget Controller Class uninitialized, please fill out BP_AuraHUD"));

    //Create the widget, 
    //then cast it to the overlay widget to get its functionality
    UUserWidget* OvlWidget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
    OverlayWidget = Cast<UAuraUserWidget>(OvlWidget);

    //Construct a new set of widget controller params,
    //then construct a new Widget Controller if one doesn't exist,
    //then set the OverlayWidget's controller to it,
    //then add the widget to the viewport
    const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

    UOverlayWidgetController* OvlWidgetController = GetOverlayWidgetController(WidgetControllerParams);
    OverlayWidget->SetWidgetController(OvlWidgetController);
    OvlWidgetController->BroadcastInitialValues();
    OvlWidget->AddToViewport();

    UAttributeMenuWidgetController* AttWidgetController = GetAttributeMenuWidgetController(WidgetControllerParams);
    AttWidgetController->BroadcastInitialValues();

}
