// Little Mario Game: Course Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMBankComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnBankStateChangedSignature, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LITTLEMARIO_API ULMBankComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULMBankComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FOnBankStateChangedSignature OnBankStateChanged;

	UFUNCTION(BlueprintCallable, Category = "Bank")
    float GetBankState() const { return BankState; }

    bool TryToAddCoin(float CoinsAmount);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bank", meta = (ClampMin = "0.0", ClampMax = "1000.0"));
    float InitialBankState = 0.0f;

	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float BankState = 0.0f;

	UFUNCTION()
    void OnTakeAnyCoin(AActor* OverlappedActor, AActor* OtherActor);

	void SetBankState(float CoinsAmount);
	
};
