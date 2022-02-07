// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTask.h"
#include "CharacterTurnGameplayTask.generated.h"



/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UCharacterTurnGameplayTask : public UGameplayTask
{
	GENERATED_BODY()

public:
	UCharacterTurnGameplayTask(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
		static UCharacterTurnGameplayTask* CharacterTurnGameplayTask(class ABaseCharacter* taskOwner, class ABaseCharacter* targetActor);
private:

	UPROPERTY()
		class ABaseCharacter* owner;
	UPROPERTY()
		class ABaseCharacter* target;

public:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
};
