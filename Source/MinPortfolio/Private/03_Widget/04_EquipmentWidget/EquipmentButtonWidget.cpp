// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/04_EquipmentWidget/EquipmentButtonWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "01_Item/ItemActor.h"
#include "01_Item/ItemType.h"
#include "01_Item/00_Equipment/EquipmentActor.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/01_Inventory/UseItemCheckWidget.h"
#include "03_Widget/03_KeyImage/KeySettingWidget.h"
#include "03_Widget/04_EquipmentWidget/EquipmentMainWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"

void UEquipmentButtonWidget::OnPressedEvnet()
{
	Image_Button->SetBrushFromTexture(hoveredImage);
}

void UEquipmentButtonWidget::OnReleasedEvnet()
{
	//Image_button->SetBrushFromTexture(defaultImage);
	GetOwningPlayer<ACustomController>()->GetPawn<APlayerCharacter>()->GetInventoryComp()->UseItem(equipmentItem);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetEquipmentWidget()->GetCanvasPanel()->SetVisibility(ESlateVisibility::Hidden);
	if(equipmentItem->GetItemInfo<FIteminfo>() != nullptr)
	{
		if(equipmentItem->GetItemInfo<FEquipment>()->equipment_Type == EEquipmentType::WEAPON)
		{
			GetOwningPlayer<ACustomController>()->GetMainWidget()->GetEquipmentWidget()->GetImage_Weapon()->SetBrushFromTexture(GetOwningPlayer<ACustomController>()->
			GetPawn<APlayerCharacter>()->GetEquipmentComp()->GetWeaponActor()->GetItemInfo<FIteminfo>()->item_Image);
		}
		else if(equipmentItem->GetItemInfo<FEquipment>()->equipment_Type == EEquipmentType::ARMOR)
		{
			if(equipmentItem->GetItemInfo<FArmor>()->armorType == EArmorType::TOP)
			{
				GetOwningPlayer<ACustomController>()->GetMainWidget()->GetEquipmentWidget()->GetImage_Armor()->SetBrushFromTexture(GetOwningPlayer<ACustomController>()->
					GetPawn<APlayerCharacter>()->GetEquipmentComp()->GetArmorActor()->GetItemInfo<FIteminfo>()->item_Image);
			}
			else if(equipmentItem->GetItemInfo<FArmor>()->armorType == EArmorType::SHOES)
			{
				GetOwningPlayer<ACustomController>()->GetMainWidget()->GetEquipmentWidget()->GetImage_Shoes()->SetBrushFromTexture(GetOwningPlayer<ACustomController>()->
					GetPawn<APlayerCharacter>()->GetEquipmentComp()->GetShoesActor()->GetItemInfo<FIteminfo>()->item_Image);
			}
		}
	}
	
}

void UEquipmentButtonWidget::OnHoveredEvnet()
{
	Image_Button->SetBrushFromTexture(hoveredImage);
}

void UEquipmentButtonWidget::OnUnhoveredEvent()
{
	Image_Button->SetBrushFromTexture(defaultImage);
}

void UEquipmentButtonWidget::SetUpButton(AItemActor* item)
{
	//auto temp = info;
	if (item != nullptr) {
		equipmentItem = item;
		item_code = equipmentItem->GetItemInfo<FIteminfo>()->item_Code;
		if (equipmentItem->GetItemInfo<FIteminfo>()->item_Image != nullptr) {
			Image_Equipment->SetBrushFromTexture(equipmentItem->GetItemInfo<FIteminfo>()->item_Image);
			
			//UE_LOG(LogTemp, Log, TEXT("%s"), Cast<AEquipmentActor>(item)->GetEquipped());
			if(Cast<AEquipmentActor>(item)->GetEquipped() == true)
			{
				Image_Button->SetBrushFromTexture(equippedImage);
			}
			else
			{
				Image_Button->SetBrushFromTexture(defaultImage);
			}
		}
	}
}

void UEquipmentButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_item->OnPressed.AddDynamic(this, &UEquipmentButtonWidget::OnPressedEvnet);
	Button_item->OnReleased.AddDynamic(this, &UEquipmentButtonWidget::OnReleasedEvnet);
	Button_item->OnHovered.AddDynamic(this, &UEquipmentButtonWidget::OnHoveredEvnet);
	Button_item->OnUnhovered.AddDynamic(this, &UEquipmentButtonWidget::OnUnhoveredEvent);

	TextBlock_Equipped->SetVisibility(ESlateVisibility::Hidden);
}
