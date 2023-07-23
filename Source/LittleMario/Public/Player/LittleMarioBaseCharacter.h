// Little Mario Game: Course Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LittleMarioBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ULMHealthComponent;
class UTextRenderComponent;

UCLASS()
class LITTLEMARIO_API ALittleMarioBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALittleMarioBaseCharacter(const FObjectInitializer& ObjInit);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    ULMHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* HealthTextComponent;



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

private:
      bool ReadyToRun = false;
	  bool IsMovingForward = false;

      void MoveForward(float AxisValue);
	  void MoveRight(float AxisValue);

	  void OnStartRunning();
	  void OnStopRunning();
};
