// Fill out your copyright notice in the Description page of Project Settings.


#include "96_Save/BattleSaveGame.h"
#include "Kismet/GameplayStatics.h"

UBattleSaveGame::UBattleSaveGame()
{
	SaveSlotName = TEXT("TestSaveSlot");
	UserIndex = 1;
}
