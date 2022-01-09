// Copyright Epic Games, Inc. All Rights Reserved.

#include "MinPortfolioGameMode.h"
#include "MinPortfolioCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMinPortfolioGameMode::AMinPortfolioGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
