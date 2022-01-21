// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "04_Skill/SkillInfomation.h"
#include "SkillTreeWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API USkillTreeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class USkillButtonWidget* UMG_Root;

	UPROPERTY()
		class USkillButtonWidget* nowButton;

	UPROPERTY(EditAnywhere)
		class UDataTable* SkillAttackTable;
	UPROPERTY(EditAnywhere)
		class UDataTable* SkillEffectTable;
	UPROPERTY(EditAnywhere)
		class UDataTable* SkillHealTable;
	UPROPERTY(EditAnywhere)
		class UDataTable* SkillPassiveTable;

public:
	UFUNCTION(BlueprintCallable)
		void GetSkillInfo_Attack(FName skill_code, class USkillButtonWidget* widget);
	UFUNCTION(BlueprintCallable)
		void GetSkillInfo_Effect(FName skill_code, class USkillButtonWidget* widget);
	UFUNCTION(BlueprintCallable)
		void GetSkillInfo_Heal(FName skill_code, class USkillButtonWidget* widget);
	UFUNCTION(BlueprintCallable)
		void GetSkillInfo_Passive(FName skill_code, class USkillButtonWidget* widget);

	class USkillButtonWidget* GetRootButton() { return UMG_Root; }

	class USkillButtonWidget* GetNowButton() { return nowButton; };
	void SetNowButton(class USkillButtonWidget* widget) { nowButton = widget; }
};
