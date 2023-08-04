// Little Mario Game: Course Project. All Rights Reserved.


#include "Components/LMHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"


DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

ULMHealthComponent::ULMHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULMHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	
	if (ComponentOwner)
	{
          ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &ULMHealthComponent::OnTakeAnyDamage);
	}
}

void ULMHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
      if (Damage <= 0.0f || IsDead() || !GetWorld()) return;

      SetHealth(Health - Damage);

	  GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	  if (IsDead())
	  {
          OnDeath.Broadcast();
        }
	  else if (AutoHeal)
	  {
          GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &ULMHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	  }
}

void ULMHealthComponent::HealUpdate()
{
     SetHealth(Health + HealModifier);

	 if (IsHealthFull() && GetWorld())
	 {
          GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	 }
}

void ULMHealthComponent::SetHealth(float NewHealth)
{
       Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
       OnHealthChanged.Broadcast(Health);
}

bool ULMHealthComponent::TryToAddHealth(float HealthAmount)
{
       if (IsDead() || IsHealthFull()) return false;

	   SetHealth(Health + HealthAmount);
       return true;
}

bool ULMHealthComponent::IsHealthFull() const
{
       return FMath::IsNearlyEqual(Health, MaxHealth);
}

