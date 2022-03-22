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

	UPROPERTY()
		class UCanvasPanel* CanvasPanel_Going;

	UPROPERTY()
		class UCanvasPanel* CanvasPanel_Shop;

	UPROPERTY()
		class UTextBlock* TextBlock_Going;

	UPROPERTY()
		class UCanvasPanel* CanvasPanel_PickUp;

	UPROPERTY()
		class UCanvasPanel* CanvasPanel_Reinforce;
	UPROPERTY()
		class UCanvasPanel* CanvasPanel_Reinforceinfo;
	UPROPERTY()
		class UCanvasPanel* CanvasPanel_ReinforceAfter;

	UPROPERTY()
		class UCanvasPanel* CanvasPanel_NPCTalk;

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
	class UCanvasPanel* GetCanvasPanel_Going() { return CanvasPanel_Going; }
	class UCanvasPanel* GetCanvasPanel_Shop() { return CanvasPanel_Shop; }
	class UTextBlock* GetTextBlock_Going() { return TextBlock_Going; }
	class UCanvasPanel* GetCanvasPanel_PickUp() { return CanvasPanel_PickUp; }
	class UCanvasPanel* GetCanvasPanel_Reinforce() { return CanvasPanel_Reinforce; }
	class UCanvasPanel* GetCanvasPanel_Reinforceinfo() { return CanvasPanel_Reinforceinfo; }
	class UCanvasPanel* GetCanvasPanel_ReinforceAfter() { return CanvasPanel_ReinforceAfter; }
	class UCanvasPanel* GetCanvasPanel_NPCTalk() { return CanvasPanel_NPCTalk; }
};
