// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Battle_SkillButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UBattle_SkillButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class ASkillBaseActor* skill;

	UPROPERTY()
		class UImage* Image_Skill;

	UPROPERTY()
		class UImage* Image_Button;

	UPROPERTY()
		class UTextBlock* TextBlock_SkillNeedAp;
	UPROPERTY()
		class UTextBlock* TextBlock_SkillName;
	UPROPERTY()
		class UTextBlock* TextBlock_SkillDec;

	UPROPERTY(EditAnywhere)
		class UTexture2D* defaultImage;
	UPROPERTY(EditAnywhere)
		class UTexture2D* hoveredImage;

public:
	virtual void NativeConstruct() override;

	void InitButton(class ASkillBaseActor* value);

	class ASkillBaseActor* GetSkill() { return skill; }

	void OnPressedEvent();
	void OnHoveredEvent();
	void OnUnhoveredEvent();

	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
};
