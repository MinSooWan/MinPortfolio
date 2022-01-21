// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMenuWidget);

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		class UEquippedItemWidget* UMG_EquippedItem;

	UPROPERTY()
		class UMenuWidget* UMG_MenuWidget;

	UPROPERTY()
		class UInventoryWidget* UMG_InventoryWidget;

	UPROPERTY()
		class UUseItemCheckWidget* UMG_UseItemCheck;

	UPROPERTY()
		class UImage* Image_BackGround;

	UPROPERTY()
		class UBackgroundBlur* BackgroundBlur_Image;

	UPROPERTY()
		class USkillLearnCheckWidget* UMG_SkillLearnCheck;

	UPROPERTY()
		class USkillMainWidget* UMG_skill;

	UPROPERTY()
		class UNeedSkillFalseWidget* UMG_NeedSkillFalse;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnMenuWidgetEvent();

public:
	class UEquippedItemWidget* GetEquippedItemWidget() { return UMG_EquippedItem; };
	class UBackgroundBlur* GetBackgroundBlur_Image() { return BackgroundBlur_Image; };
	class UImage* GetBackGroundImage() { return Image_BackGround; };
	class UUseItemCheckWidget* GetCheckWidget() { return UMG_UseItemCheck; }
	class UMenuWidget* GetMenuWidget() { return UMG_MenuWidget; }
	class UInventoryWidget* GetInventoryWidget() { return UMG_InventoryWidget; }
	class USkillLearnCheckWidget* GetSkillLearnCheck() { return UMG_SkillLearnCheck; }
	class USkillMainWidget* GetSkillMainWidget() { return UMG_skill; }
	class UNeedSkillFalseWidget* GetNeedSkillFalse() { return UMG_NeedSkillFalse; }

	FOnMenuWidget OnMenuWidget;
};
