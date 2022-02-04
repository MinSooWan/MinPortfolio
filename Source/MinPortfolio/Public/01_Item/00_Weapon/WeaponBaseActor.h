// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/00_Equipment/EquipmentActor.h"
#include "WeaponBaseActor.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API AWeaponBaseActor : public AEquipmentActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		TArray<class AActor*> hitArray;

	UFUNCTION()
		virtual void OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);

	virtual void PostInitializeComponents() override;

	virtual void ItemChange(class APlayerCharacter* player, const FEquipment* info, AItemActor* item) override;
	virtual void ItemChange_Default(class APlayerCharacter* player, const FEquipment* info, AItemActor* item) override;


	UPROPERTY(EditAnywhere)
		FName SocketName;

public:
	virtual void UseItem(class ABaseCharacter* owner) override;

	AWeaponBaseActor();

	TArray<class AActor*> GetHitArray() { return hitArray; }

	void ClearHitArray() { hitArray.Empty(); }

	FName GetSocketName() { return SocketName; }

};
