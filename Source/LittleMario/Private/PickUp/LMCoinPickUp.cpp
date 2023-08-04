// Little Mario Game: Course Project. All Rights Reserved.


#include "PickUp/LMCoinPickUp.h"
#include "Components/LMHealthComponent.h"
#include "Components/LMBankComponent.h"
#include "LMUtils.h"

bool ALMCoinPickUp::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = LMUtils::GetLMPlayerComponent<ULMHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead()) return false;

    const auto CoinComponent = LMUtils::GetLMPlayerComponent<ULMBankComponent>(PlayerPawn);
    if (!CoinComponent) return false;
    return CoinComponent->TryToAddCoin(CoinsAmount);
}
