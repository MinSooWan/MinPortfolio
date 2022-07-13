// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/09_Combination/CombinationMainWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "01_Item/00_Equipment/ArmorBaseActor.h"
#include "01_Item/00_Weapon/WeaponBaseActor.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/09_Combination/Combination_Able_Main.h"
#include "03_Widget/09_Combination/Combination_Able_OptionButton.h"
#include "03_Widget/09_Combination/Combination_Inven_PanelWidget.h"
#include "03_Widget/09_Combination/Combination_List_ButtonWidget.h"
#include "03_Widget/09_Combination/Combination_List_PanelWidget.h"
#include "03_Widget/09_Combination/Combination_Mate_PanelWidget.h"
#include "05_Combination/Combination_Mate_ButtonWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInputLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UCombinationMainWidget::OnCombination()
{
	GetOwningPlayer<ACustomController>()->SetInputMode(FInputModeUIOnly());
	UGameplayStatics::SetGamePaused(GetOwningPlayer(), true);
	SetVisibility(ESlateVisibility::Visible);
	SetFocus();
	OnAllEquipment();
	nowTypeButton = Button_All;
	nowTypeButton->WidgetStyle.Normal.SetResourceObject(hoveredTypeImage);
	applyItemList.Empty();
}

void UCombinationMainWidget::OnAllEquipment()
{
	UMG_CombinationPanel->OnAllEquipment();
	nowItem = Cast<UCombination_List_ButtonWidget>(UMG_CombinationPanel->GetVerticalBox_Combination()->GetAllChildren()[0]);
	nowItem->SetHoveredImage();
}

void UCombinationMainWidget::OnWeapon()
{
	UMG_CombinationPanel->OnWeapon();
	nowItem = Cast<UCombination_List_ButtonWidget>(UMG_CombinationPanel->GetVerticalBox_Combination()->GetAllChildren()[0]);
	nowItem->SetHoveredImage();
}

void UCombinationMainWidget::OnArmor()
{
	UMG_CombinationPanel->OnArmor();
	nowItem = Cast<UCombination_List_ButtonWidget>(UMG_CombinationPanel->GetVerticalBox_Combination()->GetAllChildren()[0]);
	nowItem->SetHoveredImage();
}

void UCombinationMainWidget::OnShoes()
{
	UMG_CombinationPanel->OnShoes();
	nowItem = Cast<UCombination_List_ButtonWidget>(UMG_CombinationPanel->GetVerticalBox_Combination()->GetAllChildren()[0]);
	nowItem->SetHoveredImage();
}

void UCombinationMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_All->OnPressed.AddDynamic(this, &UCombinationMainWidget::OnAllEquipment);
	Button_Weapon->OnPressed.AddDynamic(this, &UCombinationMainWidget::OnWeapon);
	Button_Armor->OnPressed.AddDynamic(this, &UCombinationMainWidget::OnArmor);
	Button_Shoes->OnPressed.AddDynamic(this, &UCombinationMainWidget::OnShoes);

	CanvasPanel_Mate->SetVisibility(ESlateVisibility::Hidden);
	CanvasPanel_Inven->SetVisibility(ESlateVisibility::Hidden);
}

FReply UCombinationMainWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if(InKeyEvent.GetKey() == FKey(EKeys::E) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_RightShoulder))
	{
		if (CanvasPanel_List->IsVisible()) {
			ItemTypeRight();
		}
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Q) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_LeftShoulder))
	{
		if (CanvasPanel_List->IsVisible()) {
			ItemTypeLeft();
		}
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::S) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Down))
	{
		if (CanvasPanel_List->IsVisible()) {
			ItemListDown();
		}
		else
		{
			if (CanvasPanel_Inven->IsVisible())
			{
				if (UMG_Combination_Inven_Panel->GetVerticalBox_Inven()->GetAllChildren().Num() > 0) {
					InvenDown();
				}
			}
			else
			{
				if (UMG_AbleCom->IsVisible())
				{
					if (UMG_AbleCom->GetVerticalBox_AddOption()->GetAllChildren().Num() > 0) {
						OptionDown();
					}
				}
				else
				{
					MateDown();
				}
			}
		}
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::W) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Up))
	{
		if (CanvasPanel_List->IsVisible()) {
			ItemListUp();
		}
		else
		{
			if (CanvasPanel_Inven->IsVisible())
			{
				if (UMG_Combination_Inven_Panel->GetVerticalBox_Inven()->GetAllChildren().Num() > 0) {
					InvenUp();
				}
			}
			else
			{
				if(UMG_AbleCom->IsVisible())
				{
					if (UMG_AbleCom->GetVerticalBox_AddOption()->GetAllChildren().Num() > 0) {
						OPtionUp();
					}
				}
				else {
					MateUp();
				}
			}
		}
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::SpaceBar) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Bottom))
	{
		if(CanvasPanel_List->IsVisible())
		{
			nowItem->OnPressed_List();
			nowMateItem = Cast<UCombination_Mate_ButtonWidget>(UMG_Combination_Mate_Panel->GetVerticalBox_MateList()->GetAllChildren()[0]);
			nowMateItem->SetHoveredImage();
		}
		else
		{
			if(CanvasPanel_Inven->IsVisible())
			{
				nowInvenItem->OnPressed_Inven();
			}
			else
			{
				if(UMG_AbleCom->IsVisible())
				{
					if(applyOptions.Num() < 3)
					{
						if (nowOptionButton != nullptr) {
							if (nowOptionButton->GetIsApplyOption() == false) {
								nowOptionButton->ApplyOption();
								applyOptions.Emplace(nowOptionButton->GetAddOption());
							}
						}
					}
				}
				else
				{
					if (nowMateItem->GetApplyItem() == false) {
						nowMateItem->Pressed_Mate();
						if (UMG_Combination_Inven_Panel->GetVerticalBox_Inven()->GetAllChildren().Num() > 0) {
							nowInvenItem = Cast<UCombination_List_ButtonWidget>(UMG_Combination_Inven_Panel->GetVerticalBox_Inven()->GetAllChildren()[0]);
							nowInvenItem->SetHoveredImage();
						}
					}
				}
			}
		}
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Escape) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Right))
	{
		if(CanvasPanel_List->IsVisible())
		{
			GetOwningPlayer<ACustomController>()->SetInputMode(FInputModeGameOnly());
			UGameplayStatics::SetGamePaused(GetOwningPlayer(), false);
			SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			if(CanvasPanel_Inven->IsVisible())
			{
				CanvasPanel_Inven->SetVisibility(ESlateVisibility::Hidden);

			}
			else
			{
				if(UMG_AbleCom->IsVisible())
				{
					if(applyOptions.Num() > 0)
					{
						if (nowOptionButton != nullptr) {
							if (nowOptionButton->GetIsApplyOption() == true)
							{
								nowOptionButton->UnApplyOption();
								applyOptions.Remove(nowOptionButton->GetAddOption());
							}
						}
					}
					else
					{
						UMG_AbleCom->SetVisibility(ESlateVisibility::Hidden);
						CanvasPanel_Mate->SetVisibility(ESlateVisibility::Visible);
					}
				}
				else {
					if (applyItemList.Num() > 0)
					{
						UKismetSystemLibrary::PrintString(GetOwningPlayer(), "Apply Item List Cnt is Not 0");
						if (nowMateItem->GetApplyItem() == true) {
							nowMateItem->CancelItem();
						}
						else
						{
							UKismetSystemLibrary::PrintString(GetOwningPlayer(), "Not Apply Item");
						}
					}
					else
					{
						UKismetSystemLibrary::PrintString(GetOwningPlayer(), "Apply Item List Cnt is B0");
						CanvasPanel_List->SetVisibility(ESlateVisibility::Visible);
						CanvasPanel_Mate->SetVisibility(ESlateVisibility::Hidden);
					}
				}
			}
		}
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::F) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Left))
	{
		if(CanvasPanel_Mate->IsVisible())
		{
			if(UMG_Combination_Mate_Panel->AllApItem() == true)
			{
				UMG_AbleCom->OnComAbleWidget(nowItem->GetItemInfo());
				if (UMG_AbleCom->GetVerticalBox_AddOption()->GetAllChildren().Num() > 0) {
					nowOptionButton = Cast<UCombination_Able_OptionButton>(UMG_AbleCom->GetVerticalBox_AddOption()->GetAllChildren()[0]);
					nowOptionButton->OnHoveredButton();
				}

				applyOptions.Empty();
				UMG_AbleCom->SetVisibility(ESlateVisibility::Visible);
				CanvasPanel_Mate->SetVisibility(ESlateVisibility::Hidden);
				CanvasPanel_Inven->SetVisibility(ESlateVisibility::Hidden);
			}
		}
		else if(UMG_AbleCom->IsVisible())
		{
			GetOwningPlayer<ACustomController>()->SetInputMode(FInputModeGameOnly());
			UGameplayStatics::SetGamePaused(GetOwningPlayer(), false);

			auto item = GetOwningPlayer()->GetWorld()->SpawnActor<AItemActor>(nowItem->GetItemInfo()->itemActorClass);

			for(auto iter : applyItemList)
			{
				item->SetItemStat(item->GetItemStat() + iter->GetItemStat());
			}

			if(item->IsA<AWeaponBaseActor>())
			{
				WeaponAddOption(item);
			}
			else if(item->IsA<AArmorBaseActor>())
			{
				ArmorAddOption(item);
			}

			GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComp()->AddItem(item);

			for (auto iter : applyItemList) {
				GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComp()->RemoveItem(iter);
			}

			UMG_AbleCom->SetVisibility(ESlateVisibility::Hidden);
			SetVisibility(ESlateVisibility::Hidden);
		}
	}

	GetOwningPlayer<ACustomController>()->GetMainWidget()->ChangeKeyImage(UKismetInputLibrary::Key_IsGamepadKey(InKeyEvent.GetKey()));
	return FReply::Handled();
}

void UCombinationMainWidget::ItemTypeRight()
{
	nowTypeButton->WidgetStyle.Normal.SetResourceObject(defaultTypeImage);

	if (HorizontalBox_TypeButtons->GetAllChildren().Last() != nowTypeButton) {
		auto index = HorizontalBox_TypeButtons->GetAllChildren().Find(nowTypeButton);

		nowTypeButton = Cast<UButton>(HorizontalBox_TypeButtons->GetAllChildren()[index + 1]);
	}
	else
	{
		nowTypeButton = Cast<UButton>(HorizontalBox_TypeButtons->GetAllChildren()[0]);
	}
	nowTypeButton->WidgetStyle.Normal.SetResourceObject(hoveredTypeImage);
	nowTypeButton->OnPressed.Broadcast();
}

void UCombinationMainWidget::ItemTypeLeft()
{
	nowTypeButton->WidgetStyle.Normal.SetResourceObject(defaultTypeImage);
	if (HorizontalBox_TypeButtons->GetAllChildren()[0] != nowTypeButton) {
		auto index = HorizontalBox_TypeButtons->GetAllChildren().Find(nowTypeButton);
		nowTypeButton = Cast<UButton>(HorizontalBox_TypeButtons->GetAllChildren()[index - 1]);
	}
	else
	{
		nowTypeButton = Cast<UButton>(HorizontalBox_TypeButtons->GetAllChildren().Last());
	}
	nowTypeButton->WidgetStyle.Normal.SetResourceObject(hoveredTypeImage);
	nowTypeButton->OnPressed.Broadcast();
}

void UCombinationMainWidget::ItemListDown()
{
	nowItem->SetDefaultImage();
	auto ver = UMG_CombinationPanel->GetVerticalBox_Combination();
	if(ver->GetAllChildren().Last() != nowItem)
	{
		auto index = ver->GetAllChildren().Find(nowItem);

		nowItem = Cast<UCombination_List_ButtonWidget>(ver->GetAllChildren()[index + 1]);
	}
	else
	{
		nowItem = Cast<UCombination_List_ButtonWidget>(ver->GetAllChildren()[0]);
	}
	nowItem->SetHoveredImage();
}

void UCombinationMainWidget::ItemListUp()
{
	nowItem->SetDefaultImage();
	auto ver = UMG_CombinationPanel->GetVerticalBox_Combination();
	if (ver->GetAllChildren()[0] != nowItem)
	{
		auto index = ver->GetAllChildren().Find(nowItem);

		nowItem = Cast<UCombination_List_ButtonWidget>(ver->GetAllChildren()[index - 1]);
	}
	else
	{
		nowItem = Cast<UCombination_List_ButtonWidget>(ver->GetAllChildren().Last());
	}
	nowItem->SetHoveredImage();
}

void UCombinationMainWidget::MateDown()
{
	nowMateItem->SetDefaultImage();
	auto ver = UMG_Combination_Mate_Panel->GetVerticalBox_MateList();
	if(ver->GetAllChildren().Last() != nowMateItem)
	{
		auto index = ver->GetAllChildren().Find(nowMateItem);

		nowMateItem = Cast<UCombination_Mate_ButtonWidget>(ver->GetAllChildren()[index + 1]);
	}
	else
	{
		nowMateItem = Cast<UCombination_Mate_ButtonWidget>(ver->GetAllChildren()[0]);
	}
	nowMateItem->SetHoveredImage();
}

void UCombinationMainWidget::MateUp()
{
	nowMateItem->SetDefaultImage();
	auto ver = UMG_Combination_Mate_Panel->GetVerticalBox_MateList();
	if (ver->GetAllChildren()[0] != nowMateItem)
	{
		auto index = ver->GetAllChildren().Find(nowMateItem);

		nowMateItem = Cast<UCombination_Mate_ButtonWidget>(ver->GetAllChildren()[index - 1]);
	}
	else
	{
		nowMateItem = Cast<UCombination_Mate_ButtonWidget>(ver->GetAllChildren().Last());
	}
	nowMateItem->SetHoveredImage();
}

void UCombinationMainWidget::InvenDown()
{
	nowInvenItem->SetDefaultImage();
	auto ver = UMG_Combination_Inven_Panel->GetVerticalBox_Inven();
	if(ver->GetAllChildren().Last() != nowInvenItem)
	{
		auto index = ver->GetAllChildren().Find(nowInvenItem);

		nowInvenItem = Cast<UCombination_List_ButtonWidget>(ver->GetAllChildren()[index + 1]);
	}
	else
	{
		nowInvenItem = Cast<UCombination_List_ButtonWidget>(ver->GetAllChildren()[0]);
	}
	nowInvenItem->SetHoveredImage();
}

void UCombinationMainWidget::InvenUp()
{
	nowInvenItem->SetDefaultImage();
	auto ver = UMG_Combination_Inven_Panel->GetVerticalBox_Inven();
	if (ver->GetAllChildren()[0] != nowInvenItem)
	{
		auto index = ver->GetAllChildren().Find(nowInvenItem);

		nowInvenItem = Cast<UCombination_List_ButtonWidget>(ver->GetAllChildren()[index - 1]);
	}
	else
	{
		nowInvenItem = Cast<UCombination_List_ButtonWidget>(ver->GetAllChildren().Last());
	}
	nowInvenItem->SetHoveredImage();
}

void UCombinationMainWidget::OptionDown()
{
	nowOptionButton->UnHoveredButton();
	auto ver = UMG_AbleCom->GetVerticalBox_AddOption();
	if(ver->GetAllChildren().Last() != nowOptionButton)
	{
		auto index = ver->GetAllChildren().Find(nowOptionButton);

		nowOptionButton = Cast<UCombination_Able_OptionButton>(ver->GetAllChildren()[index + 1]);
	}
	else
	{
		nowOptionButton = Cast<UCombination_Able_OptionButton>(ver->GetAllChildren()[0]);
	}
	nowOptionButton->OnHoveredButton();
}

void UCombinationMainWidget::OPtionUp()
{
	nowOptionButton->UnHoveredButton();
	auto ver = UMG_AbleCom->GetVerticalBox_AddOption();
	if(ver->GetAllChildren()[0] != nowOptionButton)
	{
		auto index = ver->GetAllChildren().Find(nowOptionButton);

		nowOptionButton = Cast<UCombination_Able_OptionButton>(ver->GetAllChildren()[index - 1]);
	}
	else
	{
		nowOptionButton = Cast<UCombination_Able_OptionButton>(ver->GetAllChildren().Last());
	}
	nowOptionButton->OnHoveredButton();
}

void UCombinationMainWidget::AddApplyItem(AItemActor* value)
{
	applyItemList.Emplace(value);
}

void UCombinationMainWidget::RemoveApplyItem(AItemActor* value)
{
	applyItemList.Remove(value);
}

void UCombinationMainWidget::WeaponAddOption(AItemActor* item)
{
	for(auto iter : applyOptions)
	{
		switch (iter)
		{
		case EAddOptionsType_Material::ADD_ATC:
			Cast<AWeaponBaseActor>(item)->AddOption_Weapon(EAddOptionsType_Equipment_Weapon::ADD_ATC);
			break;
		case EAddOptionsType_Material::ADD_DEF:
			Cast<AWeaponBaseActor>(item)->AddOption_Weapon(EAddOptionsType_Equipment_Weapon::ADD_DEF);
			break;
		case EAddOptionsType_Material::ADD_DEX:
			Cast<AWeaponBaseActor>(item)->AddOption_Weapon(EAddOptionsType_Equipment_Weapon::ADD_DEX);
			break;
		case EAddOptionsType_Material::ADD_HP:
			Cast<AWeaponBaseActor>(item)->AddOption_Weapon(EAddOptionsType_Equipment_Weapon::ADD_HP);
			break;
		case EAddOptionsType_Material::ADD_ITEM:
			Cast<AWeaponBaseActor>(item)->AddOption_Weapon(EAddOptionsType_Equipment_Weapon::ADD_ITEM);
			break;
		case EAddOptionsType_Material::ADD_EXP:
			Cast<AWeaponBaseActor>(item)->AddOption_Weapon(EAddOptionsType_Equipment_Weapon::ADD_EXP);
			break;
		case EAddOptionsType_Material::GIVE_DAMAGE:
			Cast<AWeaponBaseActor>(item)->AddOption_Weapon(EAddOptionsType_Equipment_Weapon::GIVE_DAMAGE);
			break;
		case EAddOptionsType_Material::GIVE_BURN:
			Cast<AWeaponBaseActor>(item)->AddOption_Weapon(EAddOptionsType_Equipment_Weapon::GIVE_BURN);
			break;
		case EAddOptionsType_Material::GIVE_FROZEN:
			Cast<AWeaponBaseActor>(item)->AddOption_Weapon(EAddOptionsType_Equipment_Weapon::GIVE_FROZEN);
			break;
		case EAddOptionsType_Material::GIVE_SHOCK:
			Cast<AWeaponBaseActor>(item)->AddOption_Weapon(EAddOptionsType_Equipment_Weapon::GIVE_SHOCK);
			break;
		case EAddOptionsType_Material::GIVE_SLOW:
			Cast<AWeaponBaseActor>(item)->AddOption_Weapon(EAddOptionsType_Equipment_Weapon::GIVE_SLOW);
			break;
		}
	}
}

void UCombinationMainWidget::ArmorAddOption(AItemActor* item)
{
	for (auto iter : applyOptions)
	{
		switch (iter)
		{
		case EAddOptionsType_Material::ADD_ATC:
			Cast<AArmorBaseActor>(item)->AddOption(EAddOptionsType_Equipment::ADD_ATC);
			break;
		case EAddOptionsType_Material::ADD_DEF:
			Cast<AArmorBaseActor>(item)->AddOption(EAddOptionsType_Equipment::ADD_DEF);
			break;
		case EAddOptionsType_Material::ADD_DEX:
			Cast<AArmorBaseActor>(item)->AddOption(EAddOptionsType_Equipment::ADD_DEX);
			break;
		case EAddOptionsType_Material::ADD_HP:
			Cast<AArmorBaseActor>(item)->AddOption(EAddOptionsType_Equipment::ADD_HP);
			break;
		case EAddOptionsType_Material::ADD_ITEM:
			Cast<AArmorBaseActor>(item)->AddOption(EAddOptionsType_Equipment::ADD_ITEM);
			break;
		case EAddOptionsType_Material::ADD_EXP:
			Cast<AArmorBaseActor>(item)->AddOption(EAddOptionsType_Equipment::ADD_EXP);
			break;
		}
	}
}
