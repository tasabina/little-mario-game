// Little Mario Game: Course Project. All Rights Reserved.


#include "LittleMarioModeBase.h"
#include "Player/LittleMarioBaseCharacter.h"
#include "Player/LittleMarioPlayerController.h"

ALittleMarioModeBase::ALittleMarioModeBase()
{
    // Ovveride Default Pawm Class & Player Controller
    DefaultPawnClass = ALittleMarioBaseCharacter::StaticClass();
    PlayerControllerClass = ALittleMarioPlayerController::StaticClass();
}
