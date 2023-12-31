// Little Mario Game: Course Project. All Rights Reserved.


#include "PickUp/LMBasePickUp.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ALMBasePickUp::ALMBasePickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);

}

// Called when the game starts or when spawned
void ALMBasePickUp::BeginPlay()
{
	Super::BeginPlay();

    check(CollisionComponent);

    GenerateRotationYaw();
	
}

// Called every frame
void ALMBasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));

    for (const auto OvelapPawn : OverlappingPawns)
    {
        if (GivePickupTo(OvelapPawn))
        {
            PickupWasTaken();
            break;
        }
    }
}

void ALMBasePickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);

    if (GivePickupTo(Pawn))
    {
        PickupWasTaken();
    }
    else if (Pawn)
    {
        OverlappingPawns.Add(Pawn);
    }
}

void ALMBasePickUp::NotifyActorEndOverlap(AActor* OtherActor)
{
    Super::NotifyActorEndOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);

    OverlappingPawns.Remove(Pawn);
}

bool ALMBasePickUp::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

void ALMBasePickUp::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(false, true);
    }

    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ALMBasePickUp::Respawn, RespawnTime);
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupTakenSound, GetActorLocation());
}

void ALMBasePickUp::Respawn()
{
    GenerateRotationYaw();
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(true, true);
    }
}

void ALMBasePickUp::GenerateRotationYaw()
{
    const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
    RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}

bool ALMBasePickUp::CouldBeTaken() const
{
    return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
}

