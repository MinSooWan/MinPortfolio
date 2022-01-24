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

	UPROPERTY()
		bool bOnNeedSkillWidget = false;

public:
	class UButton* GetButton_Ok() { return Button_Ok; }

	virtual void NativeConstruct() override;

	void OnNeedSkillFalse(TArray<FName> skill_Names);

	UFUNCTION()
		void OnButton_OkClickEvent();

	bool GetOnNeedSkillWidget() { return bOnNeedSkillWidget; }
};
