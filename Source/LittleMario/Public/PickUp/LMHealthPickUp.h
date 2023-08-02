// Little Mario Game: Course Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PickUp/LMBasePickUp.h"
#include "LMHealthPickUp.generated.h"

/**
 * 
 */
UCLASS()
class LITTLEMARIO_API ALMHealthPickUp : public ALMBasePickUp
{
	GENERATED_BODY()

	protected:
      UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp", meta = (ClampMin = "1.0", ClampMax = "100.0"))
      float HealthAmount = 100.0f;

	private:
	    virtual bool GivePickupTo(APawn* PlayerPawn) override;
	
};
