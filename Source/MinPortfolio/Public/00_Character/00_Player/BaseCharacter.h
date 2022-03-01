// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "00_Character/98_Object/DebuffObject.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UENUM(BlueprintType)
enum class EActionState : uint8
{
	NORMAL,
	RUN,
	ATTACK,
	ROLL,
	JUMP,
	MOVE
};

UCLASS()
class MINPORTFOLIO_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UStatusComponent* statComp;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UBuffComponent* buffComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		EActionState actionState = EActionState::NORMAL;
	UPROPERTY()
		FTimerHandle landingTimeHandle;

	UPROPERTY(EditAnywhere)
		float landingTime;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		TArray<class UDebuffObject*> debuffs;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UDebuffObject> debuffclass;

	virtual void Landed(const FHitResult& Hit) override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		FGenericTeamId myTeam;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSourceComponent;

	UPROPERTY()
		FTimerHandle AbleAction;
	UPROPERTY()
		FTimerHandle ImpossibleAction;

	UPROPERTY()
		bool bAbleAction = false;

	UPROPERTY()
		bool bMoveToTarget = false;
	UPROPERTY()
		bool bMoveToStatrLocation = false;

	UPROPERTY()
		FVector startLocation;

	UPROPERTY(EditAnywhere)
		float distanceValue;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* hitMontage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	class UStatusComponent* GetStatusComponent() { return statComp; }
	class UBuffComponent* GetBuffComp() { return buffComp; }

	enum class EActionState GetActionState() { return actionState; }

	virtual void SetActionState(const EActionState state) { }

	UFUNCTION(BlueprintCallable)
		void AddDebuffStateCharacter(EDebuffState buff, const float value, const float cool, EDebuffType type);

	UFUNCTION()
		void RemoveDebuffState(EDebuffState buff, const float value, class UDebuffObject* buffObject);

	TArray<class UDebuffObject*> GetDebuffs() { return debuffs; }
	void RemoveDebuffObejct(class UDebuffObject* buffObject);

	/** Assigns Team Agent to given TeamID */
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) { myTeam = TeamID; }

	/** Retrieve team identifier in form of FGenericTeamId */
	virtual FGenericTeamId GetGenericTeamId() const { return myTeam; }

	UFUNCTION(BlueprintCallable)
		virtual void GiveDamage(float Damage);

	UFUNCTION()
		virtual void NormalActionState(const EActionState state) { actionState = state; }

	FTimerHandle& GetAbleActionHandle() { return AbleAction; }
	FTimerHandle& GetImpossibleActionHandle() { return ImpossibleAction; }

	UFUNCTION()
		virtual void ActionChange();
	virtual void ActionChange(float cool);

	UFUNCTION()
		virtual void ActionChange_Able();
	UFUNCTION()
		virtual void ActionChange_Impossible();

	bool GetAbleAction() { return bAbleAction; }

	void SetMoveToStart(bool value) { bMoveToStatrLocation = value; }

	bool GetMoveToTarget() { return bMoveToTarget; }
	void SetMoveToTarget(bool value) { bMoveToTarget = value; }

	bool GetMoveToStatrLocation() { return bMoveToStatrLocation; }
	void SetMoveToStatrLocation(bool value) { bMoveToStatrLocation = value; }

	FVector GetStartLocation() { return startLocation; }
	void SetStartLocation(FVector value) { startLocation = value; }

	const float GetDistanceValue() { return distanceValue; }

	UFUNCTION()
		void LoadToLevel();

	UFUNCTION()
		void MonsterDieToRemove();
};
