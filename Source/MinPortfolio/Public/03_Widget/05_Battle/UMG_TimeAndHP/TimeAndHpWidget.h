// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimeAndHpWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UTimeAndHpWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UTextBlock* TextBlock_Time;
	UPROPERTY()
		class UProgressBar* ProgressBar_HP;

	UPROPERTY()
		FTimerHandle initHandle;

	UPROPERTY()
		int32 cnt = 0;

public:
	void InitTime(int32 value);
	void InitHP();

	UFUNCTION()
		void TimeTextSet();

	class UProgressBar* GetProgressBar_HP() { return ProgressBar_HP; }
};
