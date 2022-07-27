// Fill out your copyright notice in the Description page of Project Settings.


#include "98_Instance/MyGameInstance.h"
#include "MoviePlayer/Public/MoviePlayer.h"
#include "03_Widget/10_Loading/LoadingWidget.h"
#include "Blueprint/UserWidget.h"

void UMyGameInstance::ClearArrays()
{
	skill.Empty();
	inven.Empty();
	materialActors.Empty();
	haveItems.Empty();
	allMonInfo.Empty();
	monInfo = FMonsterInfo();
}

void UMyGameInstance::Init()
{
	Super::Init();

	//FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMyGameInstance::ShowLoadingScreen);
}

void UMyGameInstance::SetStat(FCharacterStat value)
{
	stat.ATC = value.ATC;
	stat.DEF = value.DEF;
	stat.DEX = value.DEX;
	stat.HP = value.HP;
	stat.MaxHP = value.MaxHP;
	stat.SkillPoint = value.SkillPoint;
}

void UMyGameInstance::ShowLoadingScreen(const FString& mapName)
{
	if(loadingWidgetClass != nullptr)
	{
		ULoadingWidget* widget = CreateWidget<ULoadingWidget>(GetWorld(), loadingWidgetClass);

		if(widget != nullptr)
		{
			widget->SetLoadLevelName(FName(*mapName));
			FLoadingScreenAttributes LoadingScreen;

			LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;

			LoadingScreen.bMoviesAreSkippable = false;

			LoadingScreen.WidgetLoadingScreen = widget->TakeWidget();

			LoadingScreen.MoviePaths.Add("LoadingMovie");

			LoadingScreen.PlaybackType = EMoviePlaybackType::MT_Looped;

			GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
			GetMoviePlayer()->PlayMovie();
		}
	}
}
