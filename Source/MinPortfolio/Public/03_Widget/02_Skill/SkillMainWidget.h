// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API USkillMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		class USkillInfoWidget* UMG_SkillInfo;
	UPROPERTY()
		class USkillTreeWidget* UMG_SkillTree;

public:

	class USkillInfoWidget* GetSkillInfoWidget() { return UMG_SkillInfo; }
	class USkillTreeWidget* GetSkillTreeWidget() { return UMG_SkillTree; }
};
