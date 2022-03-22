// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/07_Reinforce/ReinforceCheckWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "01_Item/00_Equipment/ArmorBaseActor.h"
#include "01_Item/00_Weapon/WeaponBaseActor.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/03_KeyImage/KeySettingWidget.h"
#include "03_Widget/06_Shop/ShopMainWidget.h"
#include "03_Widget/07_Reinforce/ReinforceAfterWidget.h"
#include "03_Widget/07_Reinforce/ReinforceInfoWidget.h"
#include "03_Widget/07_Reinforce/ReinforceWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Kismet/KismetInputLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UReinforceCheckWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Yes->OnPressed.AddDynamic(this, &UReinforceCheckWidget::YesButtonPressedEvent);
	Button_No->OnPressed.AddDynamic(this, &UReinforceCheckWidget::NoButtonPressedEvent);
	bIsFocusable = true;
}

FReply UReinforceCheckWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Right) || InKeyEvent.GetKey() == FKey(EKeys::E))
	{
		ChangeButton();
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Left) || InKeyEvent.GetKey() == FKey(EKeys::Q))
	{
		ChangeButton();
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Bottom) || InKeyEvent.GetKey() == FKey(EKeys::SpaceBar))
	{
		nowButton->OnPressed.Broadcast();
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Right) || InKeyEvent.GetKey() == FKey(EKeys::Escape))
	{
		NoButtonPressedEvent();
	}

	GetOwningPlayer<ACustomController>()->GetMainWidget()->ChangeKeyImage(UKismetInputLibrary::Key_IsGamepadKey(InKeyEvent.GetKey()));
	return FReply::Handled();
}

void UReinforceCheckWidget::InitCheckWidget(AItemActor* equipment_value, AItemActor* material_value)
{
	if (Button_Yes != nullptr) {
		nowButton = Button_Yes;
		nowButton->WidgetStyle.Normal.SetResourceObject(hoveredImage);
		equipmenet = equipment_value;
		mateirial = material_value;
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetOwningPlayer(), "111111111");
	}
}

void UReinforceCheckWidget::ChangeButton()
{
	if (nowButton == Button_Yes)
	{
		nowButton->WidgetStyle.Normal.SetResourceObject(defaultImage);
		nowButton = Button_No;
		nowButton->WidgetStyle.Normal.SetResourceObject(hoveredImage);
	}
	else if (nowButton == Button_No)
	{
		nowButton->WidgetStyle.Normal.SetResourceObject(defaultImage);
		nowButton = Button_Yes;
		nowButton->WidgetStyle.Normal.SetResourceObject(hoveredImage);
	}
}

void UReinforceCheckWidget::YesButtonPressedEvent()
{
	if(equipmenet->IsA<AWeaponBaseActor>())
	{
		if (Cast<AWeaponBaseActor>(equipmenet)->GetEquipped() == true) {
			for (auto iter : Cast<AWeaponBaseActor>(GetOwningPlayerPawn<APlayerCharacter>()->GetEquipmentComp()->GetWeaponActor())->GetAddOption())
			{
				switch (iter)
				{
				case EAddOptionsType_Equipment_Weapon::ADD_ATC:
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->SetATC(GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->GetATC() - 15);
					break;
				case EAddOptionsType_Equipment_Weapon::ADD_DEF:
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->SetDEF(GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->GetDEF() - 15);;
					break;
				case EAddOptionsType_Equipment_Weapon::ADD_DEX:
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->SetDEX(GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->GetDEX() - 15);
					break;
				case EAddOptionsType_Equipment_Weapon::ADD_HP:
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->SetMaxHP(GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->GetMaxHP() - 15);
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->SetHP(GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->GetHP() - 15);
					break;
				}
			}
		}

		Cast<AWeaponBaseActor>(equipmenet)->ClearAddOption();
		for(auto iter : GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_ReinforceWidget()->GetUMG_ReinforceInfo()->useAddOptions_Weapon)
		{
			Cast<AWeaponBaseActor>(equipmenet)->AddOption_Weapon(iter);

			if(Cast<AWeaponBaseActor>(equipmenet)->GetEquipped() == true)
			{
				switch (iter)
				{
				case EAddOptionsType_Equipment_Weapon::ADD_ATC:
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->AddATC(15);
					break;
				case EAddOptionsType_Equipment_Weapon::ADD_DEF:
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->AddDEF(15);
					break;
				case EAddOptionsType_Equipment_Weapon::ADD_DEX:
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->AddDEX(15);
					break;
				case EAddOptionsType_Equipment_Weapon::ADD_HP:
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->AddMaxHP(15);
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->AddHP(15);
					break;
				}
			}
		}
	}
	else if(equipmenet->IsA<AArmorBaseActor>())
	{
		if (Cast<AWeaponBaseActor>(equipmenet)->GetEquipped() == true) {
			for (auto iter : Cast<AArmorBaseActor>(GetOwningPlayerPawn<APlayerCharacter>()->GetEquipmentComp()->GetArmorActor())->GetAddOption())
			{
				switch (iter)
				{
				case EAddOptionsType_Equipment::ADD_ATC:
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->SetATC(GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->GetATC() - 15);
					break;
				case EAddOptionsType_Equipment::ADD_DEF:
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->SetDEF(GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->GetDEF() - 15);;
					break;
				case EAddOptionsType_Equipment::ADD_DEX:
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->SetDEX(GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->GetDEX() - 15);
					break;
				case EAddOptionsType_Equipment::ADD_HP:
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->SetMaxHP(GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->GetMaxHP() - 15);
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->SetHP(GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->GetHP() - 15);
					break;
				}
			}
		}

		Cast<AArmorBaseActor>(equipmenet)->ClearAddOption();
		for (auto iter : GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_ReinforceWidget()->GetUMG_ReinforceInfo()->useAddOptions_Armor)
		{
			Cast<AArmorBaseActor>(equipmenet)->AddOption(iter);

			if (Cast<AWeaponBaseActor>(equipmenet)->GetEquipped() == true)
			{
				switch (iter)
				{
				case EAddOptionsType_Equipment::ADD_ATC:
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->AddATC(15);
					break;
				case EAddOptionsType_Equipment::ADD_DEF:
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->AddDEF(15);
					break;
				case EAddOptionsType_Equipment::ADD_DEX:
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->AddDEX(15);
					break;
				case EAddOptionsType_Equipment::ADD_HP:
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->AddMaxHP(15);
					GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->AddHP(15);
					break;
				}
			}
		}
	}

	equipmenet->SetItemStat(equipmenet->GetItemStat() + mateirial->GetItemStat());

	if (Cast<AEquipmentActor>(equipmenet)->GetEquipped() == true)
	{
		GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->AddStat(mateirial->GetItemStat());
		//GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->SetMaxHP(GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->GetMaxHP() + mateirial->GetItemStat().MaxHP);
	}

	GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComp()->RemoveItem(mateirial);
	mateirial->Destroy();

	SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_ReinforceWidget()->SetVisibility(ESlateVisibility::Hidden);

	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Reinforce()->SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Reinforceinfo()->SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_ReinforceAfter()->SetVisibility(ESlateVisibility::Visible);

	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_ReinforceAfterWidget()->InitInfo(equipmenet);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_ReinforceAfterWidget()->SetVisibility(ESlateVisibility::Visible);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_ReinforceAfterWidget()->SetFocus();
}

void UReinforceCheckWidget::NoButtonPressedEvent()
{
	SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_ReinforceWidget()->GetUMG_ReinforceInfo()->SetFocus();
}
