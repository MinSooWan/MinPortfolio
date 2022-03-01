// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Battle_SkillMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UBattle_SkillMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UBattle_SkillButtonWidget> skillButtonWidget;

	UPROPERTY()
		class UScrollBox* ScrollBox_SkillList;

	UPROPERTY()
		class UBattle_SkillButtonWidget* nowSkillButton;
	UPROPERTY()
		class UBattle_SkillButtonWidget* nextSkillButton;
	UPROPERTY()
		class UBattle_SkillButtonWidget* preSkillButton;
public:

	void OnSkillList();
	void OffSkillList();

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void PressedNextButton();
	void PressedPreviousButton();
	void PressedNowButton();
};
