// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/05_Battle/UMG_Inven/Battle_InvenButtonWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/BattleController.h"
#include "01_Item/ItemActor.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/03_KeyImage/KeySettingWidget.h"
#include "03_Widget/05_Battle/UMG_Inven/Battle_InvenMainWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UBattle_InvenButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bIsFocusable = true;
}

void UBattle_InvenButtonWidget::InitButton(AItemActor* value)
{
	if (value != nullptr) {
		TextBlock_ItemNeedCp->SetText(FText::FromString("AP : " + FString::FromInt(value->GetItemInfo<FBattleItem>()->needCP)));
		auto text = FText::FromName(value->GetItemInfo<FIteminfo>()->item_Name);
		TextBlock_ItemName->SetText(text);
		TextBlock_ItemDec->SetText(FText::FromString(value->GetItemInfo<FIteminfo>()->item_Description));
		Image_Item->SetBrushFromTexture(value->GetItemInfo<FIteminfo>()->item_Image);
		item = value;
	}
}

void UBattle_InvenButtonWidget::OnPressedEvent()
{
	auto owner = GetOwningPlayerPawn<APlayerCharacter>();

	if (owner != nullptr)
	{
		GetOwningPlayer<ABattleController>()->GetMainWidget()->GetUMG_BattleInvenMain()->SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ABattleController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Battle()->SetVisibility(ESlateVisibility::Visible);
		GetOwningPlayer<ABattleController>()->SetInputMode(FInputModeGameOnly());
		SetUserFocus(GetOwningPlayer());

		UGameplayStatics::SetGamePaused(GetOwningPlayer(), false);

		owner->ActionChange_Impossible();

		owner->GetInventoryComp()->UseItem(item);

		owner->ActionChange_Impossible();
	}
}

void UBattle_InvenButtonWidget::OnHoveredEvent()
{
	Image_Button->SetBrushFromTexture(hoveredImage);
}

void UBattle_InvenButtonWidget::OnUnhoveredEvent()
{
	Image_Button->SetBrushFromTexture(defaultImage);
}

FReply UBattle_InvenButtonWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusReceived(InGeometry, InFocusEvent);

	GetOwningPlayer<ABattleController>()->GetMainWidget()->GetUMG_BattleInvenMain()->SetFocus();
	return FReply::Handled();
}
