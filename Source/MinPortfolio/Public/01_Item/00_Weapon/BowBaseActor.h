// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/00_Equipment/EquipmentActor.h"
#include "BowBaseActor.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API ABowBaseActor : public AEquipmentActor
{
	GENERATED_BODY()
	
protected:

	virtual void UseItem(class ABaseCharacter* target) override;

	virtual void ItemChange(class APlayerCharacter* player, const FWeapon* info) override;
	virtual void ItemChange_Default(class APlayerCharacter* player, const FWeapon* info) override;
};
