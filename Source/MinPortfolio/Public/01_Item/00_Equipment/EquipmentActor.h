// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemActor.h"
#include "EquipmentActor.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API AEquipmentActor : public AItemActor
{
	GENERATED_BODY()
	
protected:
	virtual void UseItem(class ABaseCharacter* target) override;

	virtual void AddStat(class ABaseCharacter* target, const FCharacterStat& statToAdd);
	virtual void RemoveStat(class ABaseCharacter* target, const FCharacterStat& statToRemove);	

	virtual void ItemChange(class APlayerCharacter* player, const FWeapon* info);
	virtual void ItemChange_Default(class APlayerCharacter* player, const FWeapon* info);

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* staticMesh;

public:

	class UStaticMeshComponent* GetStaticMesh() { return staticMesh; }
};
