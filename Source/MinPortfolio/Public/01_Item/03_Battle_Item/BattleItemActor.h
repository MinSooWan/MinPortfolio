// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemActor.h"
#include "BattleItemActor.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API ABattleItemActor : public AItemActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
		TArray<EAddOptionsType_BattleItem> addOption;

	UPROPERTY(EditAnywhere)
		EAddOptionsType_BattleItem defaultOption;

public:

	UFUNCTION(BlueprintCallable)
		virtual void AddOption(EAddOptionsType_BattleItem option);

	virtual void UseItem(class ABaseCharacter* owner) override;

	UFUNCTION()
		void SpawnPaticle(class ABaseCharacter* target);

	TArray<EAddOptionsType_BattleItem> GetAddOption() { return addOption; }
};
