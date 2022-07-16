// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/10_Loading/LoadingWidget.h"
#include "Components/ProgressBar.h"

void ULoadingWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(bTick == true)
	{
		float percent = GetAsyncLoadPercentage(levelName);

		if(percent < 0.f)
		{
			percent = 1.f;
			bTick = false;
		}

		Loading_ProgressBar->SetPercent(percent);
	}
}

void ULoadingWidget::SetLoadLevelName(const FName& name)
{
	bTick = true;
	levelName = name;
}
