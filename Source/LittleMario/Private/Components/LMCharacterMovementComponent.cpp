// Little Mario Game: Course Project. All Rights Reserved.


#include "Components/LMCharacterMovementComponent.h"
#include "Player/LittleMarioBaseCharacter.h"

float ULMCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ALittleMarioBaseCharacter* Player = Cast<ALittleMarioBaseCharacter>(GetPawnOwner());
    return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
