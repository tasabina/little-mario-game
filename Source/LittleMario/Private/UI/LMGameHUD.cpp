// Little Mario Game: Course Project. All Rights Reserved.


#include "UI/LMGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

void ALMGameHUD::DrawHUD()
{
    Super::DrawHUD();
}

void ALMGameHUD::BeginPlay()
{
    Super::BeginPlay();

    auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);

    if (PlayerHUDWidget)
    {
        PlayerHUDWidget->AddToViewport();
    }
}
