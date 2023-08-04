// Little Mario Game: Course Project. All Rights Reserved.


#include "UI/LMPlayerHUDWidget.h"
#include "Components/LMHealthComponent.h"
#include "Components/LMBankComponent.h"

float ULMPlayerHUDWidget::GetHealthPercent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return 0.0f;

    const auto Component = Player->GetComponentByClass(ULMHealthComponent::StaticClass());
    const auto HealthComponent = Cast<ULMHealthComponent>(Component);

    if (!HealthComponent) return 0.0f;

    return HealthComponent->GetHealthPercent();
}

float ULMPlayerHUDWidget::GetBankStatement() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player)
        return 0.0f;

    const auto Component = Player->GetComponentByClass(ULMBankComponent::StaticClass());
    const auto BankComponent = Cast<ULMBankComponent>(Component);

    if (!BankComponent)
        return 0.0f;

    return BankComponent->GetBankState();
}
