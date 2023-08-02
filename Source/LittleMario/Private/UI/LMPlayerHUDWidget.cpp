// Little Mario Game: Course Project. All Rights Reserved.


#include "UI/LMPlayerHUDWidget.h"
#include "Components/LMHealthComponent.h"

float ULMPlayerHUDWidget::GetHealthPercent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return 0.0f;

    const auto Component = Player->GetComponentByClass(ULMHealthComponent::StaticClass());
    const auto HealthComponent = Cast<ULMHealthComponent>(Component);

    if (!HealthComponent) return 0.0f;

    return HealthComponent->GetHealthPercent();
}
