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
	JUMP
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

	UPROPERTY()
		FGenericTeamId myTeam;
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
};
