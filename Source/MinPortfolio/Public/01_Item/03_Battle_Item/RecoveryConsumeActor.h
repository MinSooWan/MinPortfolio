// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemActor.h"
#include "RecoveryConsumeActor.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API ARecoveryConsumeActor : public AItemActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		TArray<EAddOptionsType_RecoveryItem> addOption;

public:
	UFUNCTION(BlueprintCallable)
		virtual void AddOption(EAddOptionsType_RecoveryItem option);

	virtual void UseItem(class ABaseCharacter* owner) override;

	TArray<EAddOptionsType_RecoveryItem> GetAddOption() { return addOption; }
};
