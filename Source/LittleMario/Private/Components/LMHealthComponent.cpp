// Little Mario Game: Course Project. All Rights Reserved.


#include "Components/LMHealthComponent.h"

ULMHealthComponent::ULMHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULMHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
}

