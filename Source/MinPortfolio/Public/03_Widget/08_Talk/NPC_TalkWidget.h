// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPC_TalkWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UNPC_TalkWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UTextBlock* TextBlock_NpcTalk;
	UPROPERTY()
		class UTextBlock* TextBlock_NpcName;

	UPROPERTY()
		FString nowString;

public:

	void SetNPCInfo();

	void SetNextTalkText();
	void SetPreTalkText();

	void OnNPCTalk();

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
