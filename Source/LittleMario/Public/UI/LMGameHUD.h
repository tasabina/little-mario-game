// Little Mario Game: Course Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LMGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class LITTLEMARIO_API ALMGameHUD : public AHUD
{
	GENERATED_BODY()

	public:
      virtual void DrawHUD() override;

	protected:
      UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
      TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	  virtual void BeginPlay() override;
	
};
