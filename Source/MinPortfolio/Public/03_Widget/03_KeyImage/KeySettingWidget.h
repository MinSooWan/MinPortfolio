// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeySettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UKeySettingWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	UPROPERTY()
		class UCanvasPanel* CanvasPanel_Main;

	UPROPERTY()
		class UCanvasPanel* CanvasPanel_Menu;

	UPROPERTY()
		class UCanvasPanel* CanvasPanel_Skill;
public:

	class UCanvasPanel* GetCanvasPanel_Main() { return CanvasPanel_Main; }
	class UCanvasPanel* GetCanvasPanel_Menu() { return CanvasPanel_Menu; }
	class UCanvasPanel* GetCanvasPanel_Skill() { return CanvasPanel_Skill; }
};
