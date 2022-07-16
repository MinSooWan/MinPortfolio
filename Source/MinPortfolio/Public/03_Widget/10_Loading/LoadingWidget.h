// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadingWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API ULoadingWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		class UProgressBar* Loading_ProgressBar;
	UPROPERTY()
		FName levelName;
	UPROPERTY()
		bool bTick = false;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	void SetLoadLevelName(const FName& name);
};
