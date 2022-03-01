// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/04_EquipmentWidget/EquipmentMainWidget.h"

#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/MenuWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "01_Item/ItemActor.h"
#include "01_Item/00_Equipment/EquipmentActor.h"
#include "03_Widget/04_EquipmentWidget/EquipmentButtonWidget.h"
#include "03_Widget/04_EquipmentWidget/EquipmentPanelWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Kismet/KismetInputLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UEquipmentMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Weapon->OnPressed.AddDynamic(this, &UEquipmentMainWidget::OnClickButton_Weapon);
	Button_Armor->OnPressed.AddDynamic(this, &UEquipmentMainWidget::OnClickButton_Armor);
	Button_Shoes->OnPressed.AddDynamic(this, &UEquipmentMainWidget::OnClickButton_Shoes);
}

FReply UEquipmentMainWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	GetOwningPlayer<ACustomController>()->GetMainWidget()->ChangeKeyImage(UKismetInputLibrary::Key_IsGamepadKey(InKeyEvent.GetKey()));

	if (InKeyEvent.GetKey() == FKey(EKeys::E) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_RightShoulder))
	{
		if (nowButton->Navigation->Next.Widget != nullptr)
		{
			nowButton->WidgetStyle.Normal.SetResourceObject(normalTexture);
			nowButton = Cast<UButton>(nowButton->Navigation->Next.Widget.Get());
			nowButton->WidgetStyle.Normal.SetResourceObject(hoveredTexture);
		}
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Q) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_LeftShoulder))
	{
		if (nowButton->Navigation->Previous.Widget != nullptr)
		{
			nowButton->WidgetStyle.Normal.SetResourceObject(normalTexture);
			nowButton = Cast<UButton>(nowButton->Navigation->Previous.Widget.Get());
			nowButton->WidgetStyle.Normal.SetResourceObject(hoveredTexture);
		}
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Right) || InKeyEvent.GetKey() == FKey(EKeys::D))
	{
		if (CanvasPanel->Visibility == ESlateVisibility::Visible) {
			PressedNextButton_Item();
		}
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Left) || InKeyEvent.GetKey() == FKey(EKeys::A))
	{
		if (CanvasPanel->Visibility == ESlateVisibility::Visible) {
			PressedPreviousButton_Item();
		}
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Up) || InKeyEvent.GetKey() == FKey(EKeys::W))
	{
		if (CanvasPanel->Visibility == ESlateVisibility::Visible) {
			PressedUpButton_Item();
		}
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Down) || InKeyEvent.GetKey() == FKey(EKeys::S))
	{
		if (CanvasPanel->Visibility == ESlateVisibility::Visible) {
			PressedDownButton_Item();
		}
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Escape) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Right))
	{
		if(CanvasPanel->Visibility == ESlateVisibility::Visible)
		{
			CanvasPanel->SetVisibility(ESlateVisibility::Hidden);
		}
		else {
			GetOwningPlayer<ACustomController>()->GetMainWidget()->GetBackgroundBlur_Image()->SetVisibility(ESlateVisibility::Hidden);
			GetOwningPlayer<ACustomController>()->GetMainWidget()->GetMenuWidget()->SetVisibility(ESlateVisibility::Visible);
			GetOwningPlayer<ACustomController>()->GetMainWidget()->GetMenuWidget()->GetTextBlock_MenuName()->SetText(FText::FromString(TEXT("Menu")));
			GetOwningPlayer<ACustomController>()->GetMainWidget()->GetMenuWidget()->GetEquipmentButton()->SetFocus();
			GetOwningPlayer<ACustomController>()->GetMainWidget()->OffEquipment();
			nowButton->WidgetStyle.Normal.SetResourceObject(normalTexture);
			SetVisibility(ESlateVisibility::Hidden);
		}
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::SpaceBar) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Bottom))
	{
		if(CanvasPanel->Visibility == ESlateVisibility::Visible)
		{
			nowItemButton->GetButton_item()->OnReleased.Broadcast();
		}
		else
		{
			nowButton->OnPressed.Broadcast();
		}
	}

	
	
	 return FReply::Handled();
}

void UEquipmentMainWidget::WidgetFocus(UButton* widget)
{
}

void UEquipmentMainWidget::OnClickButton_Weapon()
{
	CanvasPanel->SetVisibility(ESlateVisibility::Visible);
	UMG_EquipmentPanel->OnEquipmentWidget.Broadcast(GetOwningPlayer()->GetPawn<APlayerCharacter>()->
		GetInventoryComp(), "Weapon");
	if (UMG_EquipmentPanel->GetButtons().Num() > 0) {
		nowItemButton = UMG_EquipmentPanel->GetButtons()[0];
		nowItemButton->GetButton_item()->OnHovered.Broadcast();

		if (UMG_EquipmentPanel->GetButtons().Num() > 1)
		{
			nextItemButton = UMG_EquipmentPanel->GetButtons()[1];
			previousItemButton = UMG_EquipmentPanel->GetButtons()[UMG_EquipmentPanel->GetButtons().Num() - 1];
		}
	}
}


void UEquipmentMainWidget::OnClickButton_Armor()
{
	CanvasPanel->SetVisibility(ESlateVisibility::Visible);
	UMG_EquipmentPanel->OnEquipmentWidget.Broadcast(GetOwningPlayer()->GetPawn<APlayerCharacter>()->
		GetInventoryComp(), "Armor");
	if (UMG_EquipmentPanel->GetButtons().Num() > 0) {
		nowItemButton = UMG_EquipmentPanel->GetButtons()[0];
		nowItemButton->GetButton_item()->OnHovered.Broadcast();

		if(UMG_EquipmentPanel->GetButtons().Num() > 1)
		{
			nextItemButton = UMG_EquipmentPanel->GetButtons()[1];
			previousItemButton = UMG_EquipmentPanel->GetButtons()[UMG_EquipmentPanel->GetButtons().Num() - 1];
		}
	}
}

void UEquipmentMainWidget::OnClickButton_Shoes()
{
	CanvasPanel->SetVisibility(ESlateVisibility::Visible);
	UMG_EquipmentPanel->OnEquipmentWidget.Broadcast(GetOwningPlayer()->GetPawn<APlayerCharacter>()->
		GetInventoryComp(), "Pants");
	if (UMG_EquipmentPanel->GetButtons().Num() > 0) {
		nowItemButton = UMG_EquipmentPanel->GetButtons()[0];
		nowItemButton->GetButton_item()->OnHovered.Broadcast();
	}

	if (UMG_EquipmentPanel->GetButtons().Num() > 1)
	{
		nextItemButton = UMG_EquipmentPanel->GetButtons()[1];
		previousItemButton = UMG_EquipmentPanel->GetButtons()[UMG_EquipmentPanel->GetButtons().Num() - 1];
	}
}

void UEquipmentMainWidget::PressedNextButton_Item()
{
	if (UMG_EquipmentPanel->GetButtons().Num() > 1) {
		if(Cast<AEquipmentActor>(nowItemButton->GetEquipmentItem())->GetEquipped() == true)
		{
			nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetEquippedImage());
		}
		else {
			nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetDefaultImage());
		}
		previousItemButton = nowItemButton;
		nowItemButton = nextItemButton;

		int32 index = UMG_EquipmentPanel->GetButtons().Find(nowItemButton);
		if (index != UMG_EquipmentPanel->GetButtons().Find(UMG_EquipmentPanel->GetButtons().Last()))
		{
			nextItemButton = UMG_EquipmentPanel->GetButtons()[index + 1];
		}
		else
		{
			nextItemButton = UMG_EquipmentPanel->GetButtons()[0];
		}

		if (nowItemButton != nullptr) {
			nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetHoveredImage());
		}
	}
}

void UEquipmentMainWidget::PressedPreviousButton_Item()
{
	if (UMG_EquipmentPanel->GetButtons().Num() > 1) {
		if (Cast<AEquipmentActor>(nowItemButton->GetEquipmentItem())->GetEquipped() == true)
		{
			nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetEquippedImage());
		}
		else {
			nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetDefaultImage());
		}
		nextItemButton = nowItemButton;
		nowItemButton = previousItemButton;

		int32 index = UMG_EquipmentPanel->GetButtons().Find(nowItemButton);
		if (index != 0)
		{
			previousItemButton = UMG_EquipmentPanel->GetButtons()[index - 1];
		}
		else
		{
			previousItemButton = UMG_EquipmentPanel->GetButtons().Last();
		}

		nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetHoveredImage());
	}
}

void UEquipmentMainWidget::PressedUpButton_Item()
{
	if (UMG_EquipmentPanel->GetButtons().Num() >= 7) {
		if (Cast<AEquipmentActor>(nowItemButton->GetEquipmentItem())->GetEquipped() == true)
		{
			nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetEquippedImage());
		}
		else {
			nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetDefaultImage());
		}

		//현재 아이템 버튼을 설정
		if (UMG_EquipmentPanel->GetButtons().Find(nowItemButton) >= 6)
		{
			auto tempButton = UMG_EquipmentPanel->GetButtons()[UMG_EquipmentPanel->GetButtons().Find(nowItemButton) - 6];
			nowItemButton = tempButton;
		}
		else
		{
			int32 index = (UMG_EquipmentPanel->GetButtons().Find(UMG_EquipmentPanel->GetButtons().Last()) / 6) * 6 + UMG_EquipmentPanel->GetButtons().Find(nowItemButton);

			if (index > UMG_EquipmentPanel->GetButtons().Find(UMG_EquipmentPanel->GetButtons().Last()))
			{
				nowItemButton = UMG_EquipmentPanel->GetButtons().Last();
			}
			else
			{
				nowItemButton = UMG_EquipmentPanel->GetButtons()[index];
			}
		}

		//이전 아이템 버튼을 설정
		int32 index = UMG_EquipmentPanel->GetButtons().Find(nowItemButton);
		if (index != 0)
		{
			previousItemButton = UMG_EquipmentPanel->GetButtons()[index - 1];
		}
		else
		{
			previousItemButton = UMG_EquipmentPanel->GetButtons()[UMG_EquipmentPanel->GetButtons().Find(UMG_EquipmentPanel->GetButtons().Last())];
		}

		//다음 아이템 버튼을 설정
		if (index != UMG_EquipmentPanel->GetButtons().Find(UMG_EquipmentPanel->GetButtons().Last()))
		{
			nextItemButton = UMG_EquipmentPanel->GetButtons()[index + 1];
		}
		else
		{
			nextItemButton = UMG_EquipmentPanel->GetButtons()[0];
		}

		nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetHoveredImage());
	}
}

void UEquipmentMainWidget::PressedDownButton_Item()
{
	if (UMG_EquipmentPanel->GetButtons().Num() >= 7) {
		if (Cast<AEquipmentActor>(nowItemButton->GetEquipmentItem())->GetEquipped() == true)
		{
			nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetEquippedImage());
		}
		else {
			nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetDefaultImage());
		}

		int32 index = UMG_EquipmentPanel->GetButtons().Find(nowItemButton);
		int32 lastIndex = UMG_EquipmentPanel->GetButtons().Find(UMG_EquipmentPanel->GetButtons().Last());
		//현재 아이템 버튼을 설정
		if (index < lastIndex - (lastIndex % 6))
		{
			if (index + 6 <= lastIndex)
			{
				nowItemButton = UMG_EquipmentPanel->GetButtons()[index + 6];
			}
			else
			{
				nowItemButton = UMG_EquipmentPanel->GetButtons().Last();
			}
		}
		else
		{
			nowItemButton = UMG_EquipmentPanel->GetButtons()[index - (lastIndex / 6) * 6];
		}

		//이전 아이템 버튼을 설정
		index = UMG_EquipmentPanel->GetButtons().Find(nowItemButton);
		if (index != 0)
		{
			previousItemButton = UMG_EquipmentPanel->GetButtons()[index - 1];
		}
		else
		{
			previousItemButton = UMG_EquipmentPanel->GetButtons()[lastIndex];
		}

		//다음 아이템 버튼을 설정
		if (index != lastIndex)
		{
			nextItemButton = UMG_EquipmentPanel->GetButtons()[index + 1];
		}
		else
		{
			nextItemButton = UMG_EquipmentPanel->GetButtons()[0];
		}

		nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetHoveredImage());
	}
}

void UEquipmentMainWidget::OnEquipmentWidget()
{
	SetVisibility(ESlateVisibility::Visible);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetBackgroundBlur_Image()->SetVisibility(ESlateVisibility::Visible);
	SetFocus();
	nowButton = Button_Weapon;
	nowButton->WidgetStyle.Normal.SetResourceObject(hoveredTexture);

	SetItemImage();
}

void UEquipmentMainWidget::SetItemImage()
{
	if (GetOwningPlayer<ACustomController>()->GetPawn<APlayerCharacter>()->GetEquipmentComp()->GetWeaponActor() != nullptr &&
		GetOwningPlayer<ACustomController>()->GetPawn<APlayerCharacter>()->GetEquipmentComp()->GetArmorActor() != nullptr &&
		GetOwningPlayer<ACustomController>()->GetPawn<APlayerCharacter>()->GetEquipmentComp()->GetShoesActor() != nullptr)
	{
		Image_Weapon->SetBrushFromTexture(GetOwningPlayer<ACustomController>()->GetPawn<APlayerCharacter>()->GetEquipmentComp()->
			GetWeaponActor()->GetItemInfo<FIteminfo>()->item_Image);
		Image_Armor->SetBrushFromTexture(GetOwningPlayer<ACustomController>()->GetPawn<APlayerCharacter>()->GetEquipmentComp()->
			GetArmorActor()->GetItemInfo<FIteminfo>()->item_Image);
		Image_Shoes->SetBrushFromTexture(GetOwningPlayer<ACustomController>()->GetPawn<APlayerCharacter>()->GetEquipmentComp()->
			GetShoesActor()->GetItemInfo<FIteminfo>()->item_Image);
	}
}
