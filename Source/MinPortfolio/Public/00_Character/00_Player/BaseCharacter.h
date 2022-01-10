// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
		EActionState actionState = EActionState::NORMAL;

	UPROPERTY()
		FTimerHandle landingTimeHandle;

	UPROPERTY(EditAnywhere)
		float landingTime;

	virtual void Landed(const FHitResult& Hit) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	class UStatusComponent* GetStatusComponent() { return statComp; }

	enum class EActionState GetActionState() { return actionState; }

	virtual void SetActionState(const EActionState state) { }
};
