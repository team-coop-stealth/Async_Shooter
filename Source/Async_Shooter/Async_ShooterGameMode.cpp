// Copyright Epic Games, Inc. All Rights Reserved.

#include "Async_ShooterGameMode.h"
#include "Async_ShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAsync_ShooterGameMode::AAsync_ShooterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
