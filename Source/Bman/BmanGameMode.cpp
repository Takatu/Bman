// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BmanGameMode.h"
#include "BmanPlayerController.h"
#include "BmanCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABmanGameMode::ABmanGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ABmanPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}