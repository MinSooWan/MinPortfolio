// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "01_Item/ItemType.h"
#include "EquipmentComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINPORTFOLIO_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AItemActor> defaultWeaponActorClass;
	UPROPERTY()
		class AItemActor* defaultWeaponActor;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AItemActor> defaultArmorActorClass;
	UPROPERTY()
		class AItemActor* defaultArmorActor;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class AItemActor* weaponActor;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class AItemActor* armorActor;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void EquipmentCompInit();

	class AItemActor* GetWeaponActor() { return weaponActor; }
	class AItemActor* GetArmorActor() { return armorActor; }

	void SetWeaponActor(const FIteminfo& itemInfo, class AItemActor* item);
	void SetArmorActor(const FIteminfo& itemInfo, class AItemActor* item);
	
	class AItemActor* GetDefaultWeaponActor() { return defaultWeaponActor; }
	class AItemActor* GetDefaultArmorActor() { return defaultArmorActor; }
};
