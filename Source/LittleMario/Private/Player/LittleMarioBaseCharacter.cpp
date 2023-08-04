// Little Mario Game: Course Project. All Rights Reserved.


#include "Player/LittleMarioBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/LMCharacterMovementComponent.h"
#include "Components/LMHealthComponent.h"
#include "Components/LMBankComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacterLog, All, All);

// Sets default values
ALittleMarioBaseCharacter::ALittleMarioBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<ULMCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

	CameraComponent->bUsePawnControlRotation = true;

    HealthComponent = CreateDefaultSubobject<ULMHealthComponent>("HealthComponent");
    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());

    BankComponent = CreateDefaultSubobject<ULMBankComponent>("BankComponent");
    BankTextComponent = CreateDefaultSubobject<UTextRenderComponent>("BankTextComponent");
    BankTextComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ALittleMarioBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

    check(HealthComponent);
    check(HealthTextComponent);
    check(BankComponent);
    check(BankTextComponent);
    check(GetCharacterMovement());

    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &ALittleMarioBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ALittleMarioBaseCharacter::OnHealthChanged);

    OnBankStateChanged(BankComponent->GetBankState());
    BankComponent->OnBankStateChanged.AddUObject(this, &ALittleMarioBaseCharacter::OnBankStateChanged);

    LandedDelegate.AddDynamic(this, &ALittleMarioBaseCharacter::OnGroundLanded);
}

// Called every frame
void ALittleMarioBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ALittleMarioBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ALittleMarioBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ALittleMarioBaseCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ALittleMarioBaseCharacter::OnStopRunning);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALittleMarioBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ALittleMarioBaseCharacter::MoveRight);

    PlayerInputComponent->BindAxis("LookUp", this, &ALittleMarioBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ALittleMarioBaseCharacter::AddControllerYawInput);

}

bool ALittleMarioBaseCharacter::IsRunning() const
{
    return ReadyToRun &&  IsMovingForward && !GetVelocity().IsZero();
}

float ALittleMarioBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero()) return 0.0f;
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
    return  CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ALittleMarioBaseCharacter::MoveForward(float AxisValue)
{
    IsMovingForward = AxisValue > 0.0f;

    UE_LOG(LogTemp, Warning, TEXT("%f"), AxisValue);

	if ((Controller != NULL) && (AxisValue != 0.0f))
	{
          const FRotator Rotation = Controller->GetControlRotation();
          const FRotator YawRotation(0, Rotation.Yaw, 0);

		  const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
          AddMovementInput(Direction, AxisValue);
	}
}

void ALittleMarioBaseCharacter::MoveRight(float AxisValue)
{
      if ((Controller != NULL) && (AxisValue != 0.0f))
      {
          const FRotator Rotation = Controller->GetControlRotation();
          const FRotator YawRotation(0, Rotation.Yaw, 0);

          const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
          AddMovementInput(Direction, AxisValue);
      }
}

void ALittleMarioBaseCharacter::OnStartRunning()
{
      ReadyToRun = true;
}

void ALittleMarioBaseCharacter::OnStopRunning()
{
      ReadyToRun = false;
}

void ALittleMarioBaseCharacter::OnDeath()
{
      UE_LOG(LogBaseCharacterLog, Display, TEXT("Player %s is dead"), *GetName());
      PlayAnimMontage(DeathAnimMontage);

      GetCharacterMovement()->DisableMovement();

      SetLifeSpan(5.0f);

      if (Controller)
      {
          Controller->ChangeState(NAME_Spectating);
      }
}

void ALittleMarioBaseCharacter::OnHealthChanged(float Health)
{
      HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ALittleMarioBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
      const auto FallVelocityZ = -GetVelocity().Z;

      if (FallVelocityZ < LandedDamageVelocity.X) return;

      const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);

      TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void ALittleMarioBaseCharacter::OnBankStateChanged(float CoinAmounts)
{
      BankTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), CoinAmounts)));
}


