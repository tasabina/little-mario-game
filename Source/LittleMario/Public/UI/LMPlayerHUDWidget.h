// Little Mario Game: Course Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LMPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class LITTLEMARIO_API ULMPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
      UFUNCTION(BlueprintCallable, Category = "UI")
      float GetHealthPercent() const;
	
};
