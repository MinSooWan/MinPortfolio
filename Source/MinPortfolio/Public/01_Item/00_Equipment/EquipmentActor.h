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
	virtual void UseItem(class ABaseCharacter* owner) override;

	virtual void AddStat(class ABaseCharacter* target, const FCharacterStat& statToAdd);
	virtual void RemoveStat(class ABaseCharacter* target, const FCharacterStat& statToRemove);	

	virtual void ItemChange(class APlayerCharacter* player, const FEquipment* info, AItemActor* item);
	virtual void ItemChange_Default(class APlayerCharacter* player, const FEquipment* info, AItemActor* item);

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* staticMesh;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* AttackParticle;

	UPROPERTY()
		bool bEquipped = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<EAddOptionsType_Equipment> addOption;

public:

	UFUNCTION(BlueprintCallable)
		virtual void AddOption(EAddOptionsType_Equipment option);

	TArray<EAddOptionsType_Equipment> GetAddOption() { return addOption; }

	AEquipmentActor();

	class UStaticMeshComponent* GetStaticMesh() { return staticMesh; }

	class UParticleSystem* GetAttackParticle() { return AttackParticle; }

	bool GetEquipped() { return bEquipped; }
	void SetEquipped(bool value) { bEquipped = value; }
};
