// Little Mario Game: Course Project. All Rights Reserved.


#include "Components/LMBankComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "PickUp/LMCoinPickUp.h"

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

	  //AActor* ComponentOwner = GetOwner();

   //   if (ComponentOwner)
   //   {
   //       ComponentOwner->OnActorBeginOverlap.AddDynamic(this, &ULMBankComponent::OnTakeAnyCoin);
   //   }
}


bool ULMBankComponent::TryToAddCoin(float CoinsAmount)
{
      UE_LOG(LogBankStateComponent, Warning, TEXT("Coins: %f"), BankState);
      SetBankState(BankState + CoinsAmount);
      return true;
}

//void ULMBankComponent::OnTakeAnyCoin(AActor* OverlappedActor, AActor* OtherActor)
//{
//      if (!OtherActor || !GetWorld()) return;
//
//      ALMCoinPickUp* CoinPickUp = Cast<ALMCoinPickUp>(OtherActor);
//
//      if (CoinPickUp)
//      {
//          UE_LOG(LogBankStateComponent, Warning, TEXT("OtherActor: %f"), CoinPickUp->GetCoinsAmount());
//
//          const float CoinsAmount = CoinPickUp->GetCoinsAmount();
//
//          SetBankState(BankState + CoinsAmount);
//
//          UE_LOG(LogBankStateComponent, Warning, TEXT("%f"), BankState);
//      }
//      else
//      {
//          return;
//      }
//}

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

