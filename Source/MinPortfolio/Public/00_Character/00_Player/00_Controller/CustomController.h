// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomController.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API ACustomController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void OnPossess(APawn* aPawn) override;

	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMainWidget> mainWidgetClass;

	UPROPERTY(BlueprintReadOnly)
		class UMainWidget* mainWidget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABattleCharacter> BattleCharacterClass;

public:
	class UMainWidget* GetMainWidget() { return mainWidget; }

	void ChangeBattleCharacter();
};
