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

	UPROPERTY()
		class UCanvasPanel* CanvasPanel_Inven;

	UPROPERTY()
		class UCanvasPanel* CanvasPanel_Equipment;

	UPROPERTY()
		class UCanvasPanel* CanvasPanel_Battle;

	UPROPERTY()
		class UCanvasPanel* CanvasPanel_Attack;

	UPROPERTY()
		class UCanvasPanel* CanvasPanel_Battle_Skill;

	UPROPERTY()
		class UCanvasPanel* CanvasPanel_Item;

public:

	class UCanvasPanel* GetCanvasPanel_Main() { return CanvasPanel_Main; }
	class UCanvasPanel* GetCanvasPanel_Menu() { return CanvasPanel_Menu; }
	class UCanvasPanel* GetCanvasPanel_Skill() { return CanvasPanel_Skill; }
	class UCanvasPanel* GetCanvasPanel_Inven() { return CanvasPanel_Inven; }
	class UCanvasPanel* GetCanvasPanel_Equipment() { return CanvasPanel_Equipment; }
	class UCanvasPanel* GetCanvasPanel_Battle() { return CanvasPanel_Battle; }
	class UCanvasPanel* GetCanvasPanel_Attack() { return CanvasPanel_Attack; }
	class UCanvasPanel* GetCanvasPanel_Battle_Skill() { return CanvasPanel_Battle_Skill; }
	class UCanvasPanel* GetCanvasPanel_Item() { return CanvasPanel_Item; }
};
