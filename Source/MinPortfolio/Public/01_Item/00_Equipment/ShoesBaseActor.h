// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/00_Equipment/EquipmentActor.h"
#include "ShoesBaseActor.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API AShoesBaseActor : public AEquipmentActor
{
	GENERATED_BODY()

protected:
	virtual void ItemChange(class APlayerCharacter* player, const FEquipment* info, AItemActor* item) override;
	virtual void ItemChange_Default(class APlayerCharacter* player, const FEquipment* info, AItemActor* item) override;

public:

	virtual void AddOption(EAddOptionsType_Equipment option) override;
	virtual void UseItem(class ABaseCharacter* owner) override;
};
