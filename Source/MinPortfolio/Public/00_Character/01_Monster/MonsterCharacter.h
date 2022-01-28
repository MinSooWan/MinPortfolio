// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/00_Player/BaseCharacter.h"
#include "MonsterCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API AMonsterCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:

	AMonsterCharacter();

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

protected:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ATriggerSphere> triggerClass;
	UPROPERTY()
		class ATriggerSphere* moveZone;

	UPROPERTY(EditAnywhere)
		class UBehaviorTree* aiTree;
	UPROPERTY(EditAnywhere)
		AActor* targetLocation;
	UPROPERTY()
		bool bMoving = false;

	UPROPERTY()
		FTimerHandle movingHandle;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		FVector homeLocation;
public:
	FTimerHandle GetMovingHandle() { return movingHandle; }
	bool GetMoving() { return bMoving; }


	class UBehaviorTree* GetAiTree() { return aiTree; }
	AActor* GetTargetActorLocation() { return targetLocation; }

	UFUNCTION()
		void OnActorEndOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);
};
