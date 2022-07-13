// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/09_Combination/Combination_Able_OptionButton.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UCombination_Able_OptionButton::SetButtonOption(EAddOptionsType_Material value)
{
	addOption = value;
	TextBlock_Name->Text = FText::FromString(GetAddOptionDescription_Material(value));
}

void UCombination_Able_OptionButton::OnHoveredButton()
{
	Image_Sel->SetBrushFromTexture(hoveredImage);
}

void UCombination_Able_OptionButton::UnHoveredButton()
{
	Image_Sel->SetBrushFromTexture(defaultImage);
}

void UCombination_Able_OptionButton::ApplyOption()
{
	bApplyOption = true;
	Image_backG->SetBrushFromTexture(applyImage);
}

void UCombination_Able_OptionButton::UnApplyOption()
{
	bApplyOption = false;
	Image_backG->SetBrushFromTexture(defaultImage_apply);
}

FString UCombination_Able_OptionButton::GetAddOptionDescription_Material(EAddOptionsType_Material option)
{
	FString str;
	switch (option)
	{
	case EAddOptionsType_Material::ADD_ATC:
		str = TEXT("공격력 강화");
		return str;
	case EAddOptionsType_Material::ADD_DEF:
		str = TEXT("방어력 강화");
		return str;
	case EAddOptionsType_Material::ADD_DEX:
		str = TEXT("민첩성 강화");
		return str;
	case EAddOptionsType_Material::ADD_EXP:
		str = TEXT("빠른 성장");
		return str;
	case EAddOptionsType_Material::ADD_HP:
		str = TEXT("체력 강화");
		return str;
	case EAddOptionsType_Material::ADD_ITEM:
		str = TEXT("더 많이!");
		return str;
	case EAddOptionsType_Material::GIVE_ATC_DOWN:
		str = TEXT("무력의 저주");
		return str;
	case EAddOptionsType_Material::GIVE_BURN:
		str = TEXT("광열의 열기");
		return str;
	case EAddOptionsType_Material::GIVE_DAMAGE:
		str = TEXT("강력한 파괴력");
		return str;
	case EAddOptionsType_Material::GIVE_DEF_DOWN:
		str = TEXT("방어의 저주");
		return str;
	case EAddOptionsType_Material::GIVE_FROZEN:
		str = TEXT("빙괴의 반향");
		return str;
	case EAddOptionsType_Material::GIVE_SHOCK:
		str = TEXT("봉뢰의 마찰");
		return str;
	case EAddOptionsType_Material::GIVE_SLOW:
		str = TEXT("속도의 저주");
		return str;
	case EAddOptionsType_Material::RECOVERY_HP:
		str = TEXT("강력한 회복력");
		return str;
	case EAddOptionsType_Material::ADD_ATC_TIME:
		str = TEXT("익스클루시브 스펠");
		return str;
	case EAddOptionsType_Material::ADD_DEF_TIME:
		str = TEXT("강력한 회복력");
		return str;
	case EAddOptionsType_Material::ADD_DEX_TIME:
		str = TEXT("아이언 바디");
		return str;
	case EAddOptionsType_Material::ADD_HP_TIME:
		str = TEXT("리스토네이션");
		return str;
	}return str;
}
