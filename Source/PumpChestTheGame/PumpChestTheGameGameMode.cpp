// Copyright Epic Games, Inc. All Rights Reserved.

#include "PumpChestTheGameGameMode.h"
#include "PumpChestTheGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

APumpChestTheGameGameMode::APumpChestTheGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
