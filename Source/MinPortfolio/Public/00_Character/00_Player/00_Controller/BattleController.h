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

	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* aPawn) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMainWidget> mainWidgetClass;

	UPROPERTY(BlueprintReadOnly)
		class UMainWidget* mainWidget;

public:

	class UMainWidget* GetMainWidget() { return mainWidget; }

	void OnPreesedSkillList();
	void OnPreesedInvenList();
};
