// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/02_Skill/SkillMainWidget.h"

#include "03_Widget/02_Skill/SkillButtonWidget.h"
#include "03_Widget/02_Skill/SkillTreeWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"

void USkillMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UMG_SkillTree->GetRootButton()->GetImage_Skill()->SetVisibility(ESlateVisibility::Hidden);
}
