// Little Mario Game: Course Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PickUp/LMBasePickUp.h"
#include "LMCoinPickUp.generated.h"

/**
 * 
 */
UCLASS()
class LITTLEMARIO_API ALMCoinPickUp : public ALMBasePickUp
{
	GENERATED_BODY()

	//public:
 //     float GetCoinsAmount() const { return CoinsAmount; }

	protected:
      UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp", meta = (ClampMin = "1.0", ClampMax = "10.0"))
      float CoinsAmount = 10;

	private:
      virtual bool GivePickupTo(APawn* PlayerPawn) override;
	
};
