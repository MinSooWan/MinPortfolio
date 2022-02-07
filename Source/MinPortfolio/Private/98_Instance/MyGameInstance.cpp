// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Instance/MyGameInstance.h"

void UMyGameInstance::SetStat(FCharacterStat value)
{
	stat.ATC = value.ATC;
	stat.DEF = value.DEF;
	stat.DEX = value.DEX;
	stat.HP = value.HP;
	stat.MaxHP = value.MaxHP;
}
