// Little Mario Game: Course Project. All Rights Reserved.


#include "PickUp/LMHealthPickUp.h"
#include "Components/LMHealthComponent.h"

bool ALMHealthPickUp::GivePickupTo(APawn* PlayerPawn)
{
    // const auto HealthComponent = LMUtils::GetLMPlayerComponent<ULMHealthComponent>(PlayerPawn);
    // if (!HealthComponent) return false;

    // return HealthComponent->TryToAddHealth(HealthAmount);

    return true;
}
