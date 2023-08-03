// Little Mario Game: Course Project. All Rights Reserved.


#include "Components/LMBankComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogBankStateComponent, All, All);
// Sets default values for this component's properties
ULMBankComponent::ULMBankComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void ULMBankComponent::BeginPlay()
{
      Super::BeginPlay();

	  check(InitialBankState >= 0);

	  SetBankState(InitialBankState);

	  AActor* ComponentOwner = GetOwner();

      if (ComponentOwner)
      {
          ComponentOwner->OnActorBeginOverlap.AddDynamic(this, &ULMBankComponent::OnTakeAnyCoin);
      }
}


bool ULMBankComponent::TryToAddCoin(float CoinsAmount)
{
      return false;
}

void ULMBankComponent::OnTakeAnyCoin(AActor* OverlappedActor, AActor* OtherActor)
{
      if (!OtherActor || !GetWorld()) return;

      UE_LOG(LogBankStateComponent, Warning, TEXT("OtherActor: %s"), *FString(OtherActor->GetName()));

      SetBankState(BankState + 1.0f);

      UE_LOG(LogBankStateComponent, Warning, TEXT("%f"), BankState);

}

void ULMBankComponent::SetBankState(float CoinsAmount)
{
      UE_LOG(LogBankStateComponent, Warning, TEXT("Coins amount: %f"), CoinsAmount);
      BankState = CoinsAmount;
      OnBankStateChanged.Broadcast(BankState);
}


// Called every frame
void ULMBankComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

