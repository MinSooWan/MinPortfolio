// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMenuWidget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeKeyMode, bool, IsKeyMode);

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
		TMap<FKey, class UTexture2D*> keyImage;

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

	UPROPERTY()
		class UNeedSpLackWidget* UMG_NeedSPLack;

	UPROPERTY()
		class UKeySettingWidget* UMG_Key;

	UPROPERTY()
		class UEquipmentMainWidget* UMG_EquipmentMain;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnMenuWidgetEvent();

	UPROPERTY(BlueprintReadWrite)
		TArray<class UUserWidget*> keyImages_key;
	UPROPERTY(BlueprintReadWrite)
		TArray<class UUserWidget*> keyImages_pad;

public:
	const TMap<FKey, class UTexture2D*> GetKeyImage() { return keyImage; }

	TArray<class UUserWidget*> GetKeyImages_Key() { return keyImages_key; }
	TArray<class UUserWidget*> GetKeyImages_Pad() { return keyImages_pad; }

	void InitKeyImage();

	UFUNCTION(BlueprintCallable)
		void ChangeKeyImage(bool IsKeyMode);

	void OnMenu();
	void OffMenu();

	void OnInven();
	void OffInven();

	void OnSkillTree();
	void OffSkillTree();

	class UEquippedItemWidget* GetEquippedItemWidget() { return UMG_EquippedItem; };
	class UBackgroundBlur* GetBackgroundBlur_Image() { return BackgroundBlur_Image; };
	class UImage* GetBackGroundImage() { return Image_BackGround; };
	class UUseItemCheckWidget* GetCheckWidget() { return UMG_UseItemCheck; }
	class UMenuWidget* GetMenuWidget() { return UMG_MenuWidget; }
	class UInventoryWidget* GetInventoryWidget() { return UMG_InventoryWidget; }
	class USkillLearnCheckWidget* GetSkillLearnCheck() { return UMG_SkillLearnCheck; }
	class USkillMainWidget* GetSkillMainWidget() { return UMG_skill; }
	class UNeedSkillFalseWidget* GetNeedSkillFalse() { return UMG_NeedSkillFalse; }
	class UNeedSpLackWidget* GetNeedSPLack() { return UMG_NeedSPLack; }
	class UKeySettingWidget* GetKeySetting() { return UMG_Key; }
	class UEquipmentMainWidget* GetEquipmentWidget() { return UMG_EquipmentMain; }

	FOnMenuWidget OnMenuWidget;
	FChangeKeyMode ChangeKeyMode;
};
