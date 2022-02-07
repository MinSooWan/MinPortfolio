// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattleController.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API ABattleController : public APlayerController
{
	GENERATED_BODY()

protected: 

	UPROPERTY(EditAnywhere)
		TMap<FKey, class UImage*> keyImage;

	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* aPawn) override;

public:
	const TMap<FKey, class UImage*> GetKeyImage() { return keyImage; }
};
