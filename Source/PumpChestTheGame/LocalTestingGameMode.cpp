// Copyright Epic Games, Inc. All Rights Reserved.

#include "LocalTestingGameMode.h"
#include "LocalTestingCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MyHUD.h"

ALocalTestingGameMode::ALocalTestingGameMode()
{
	HUDClass = AMyHUD::StaticClass();
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
