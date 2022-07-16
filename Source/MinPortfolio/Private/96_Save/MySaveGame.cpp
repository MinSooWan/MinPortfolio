// Fill out your copyright notice in the Description page of Project Settings.


#include "96_Save/MySaveGame.h"

UMySaveGame::UMySaveGame()
{
	SaveSlotName = TEXT("SaveGame");
	UserIndex = 1;
}

void UMySaveGame::ClearArray()
{
	skill.Empty();
	inven.Empty();
	haveItems.Empty();
}
