// Little Mario Game: Course Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMBasePickUp.generated.h"

class USphereComponent;

UCLASS()
class LITTLEMARIO_API ALMBasePickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALMBasePickUp();

protected:
    UPROPERTY(VisibleAnywhere, Category = "PickUp")
    USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "PickUp")
    float RespawnTime = 5.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    float RotationYaw = 0.0f;

    virtual bool GivePickupTo(APawn* PlayerPawn);

    void PickupWasTaken();
    void Respawn();
    void GenerateRotationYaw();

};
