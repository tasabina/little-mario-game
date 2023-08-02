// Little Mario Game: Course Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LMCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class LITTLEMARIO_API ULMCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	public:
      UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.5", ClampMax = "10.0"))
      float RunModifier = 2.0f;

      virtual float GetMaxSpeed() const override;
	
};
