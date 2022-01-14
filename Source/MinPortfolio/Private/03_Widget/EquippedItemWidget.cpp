// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/EquippedItemWidget.h"
#include "Components/Image.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/ToolComponent.h"
#include "01_Item/ItemActor.h"
#include "00_Character/99_Component/EquipmentComponent.h"

void UEquippedItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	InitImage();
}

void UEquippedItemWidget::InitImage(){
	APlayerCharacter* player = GetOwningPlayerPawn<APlayerCharacter>();

	if (player != nullptr) {
		if(player->GetToolComp()==nullptr)
		{
			return;
		}

		if(player->GetToolComp()->GetToolActor()==nullptr)
		{
			return;
		}


		auto info = player->GetToolComp()->GetToolActor()->GetItemInfo<FIteminfo>();
		if (info != nullptr) {
			Image_Tool->SetBrushFromTexture(player->GetToolComp()->GetToolActor()->GetItemInfo<FIteminfo>()->item_Image);
			Image_Weapon->SetBrushFromTexture(player->GetEquipmentComp()->GetWeaponActor()->GetItemInfo<FIteminfo>()->item_Image);
		}
	}
}
