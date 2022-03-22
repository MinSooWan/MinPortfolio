// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/05_Battle/UMG_TimeAndHP/TimeAndHpWidget.h"

#include "00_Character/00_Player/BaseCharacter.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"

void UTimeAndHpWidget::InitTime(int32 value)
{
	cnt = value;
	TextBlock_Time->SetText(FText::FromString(FString::FromInt(cnt) + TEXT("초")));
	
	FTimerDelegate timerDel;
	timerDel.BindUFunction(this, "TimeTextSet");
	GetOwningPlayer()->GetWorld()->GetTimerManager().SetTimer(initHandle, timerDel, 1, true);
}

void UTimeAndHpWidget::InitHP()
{
	if (GetOwningPlayerPawn()->IsA<AMonsterCharacter>()) {
		ProgressBar_HP->SetPercent(GetOwningPlayerPawn<AMonsterCharacter>()->GetStatusComponent()->GetHP() / GetOwningPlayerPawn<AMonsterCharacter>()->GetStatusComponent()->GetMaxHP());
	}
	else if(GetOwningPlayerPawn()->IsA<APlayerCharacter>())
	{
		ProgressBar_HP->SetPercent(GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->GetHP() / GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->GetMaxHP());
	}
}

void UTimeAndHpWidget::TimeTextSet()
{
	cnt -= 1;
	TextBlock_Time->SetText(FText::FromString(FString::FromInt(cnt) + TEXT("초")));
	if(cnt == 0)
	{
		GetOwningPlayer()->GetWorld()->GetTimerManager().ClearTimer(initHandle);
	}
}
