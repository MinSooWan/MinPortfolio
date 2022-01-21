// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NeedSkillFalseWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UNeedSkillFalseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		class UButton* Button_Ok;
	UPROPERTY()
		class UTextBlock* TextBlock_NeedSkill;

public:
	virtual void NativeConstruct() override;

	void OnNeedSkillFalse(FName skill_Name);

	UFUNCTION()
		void OnButton_OkClickEvent();
};
