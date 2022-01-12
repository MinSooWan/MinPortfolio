// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/00_Player/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

public:
	APlayerCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UInventoryComponent* inventoryComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UEquipmentComponent* equipmentComp;

	UPROPERTY(VisibleAnywhere)
		class UChildActorComponent* WeaponChild;

	UPROPERTY(VisibleAnywhere)
		class UChildActorComponent* BowChild;

	virtual void BeginPlay() override;

	virtual void Jump() override;

	virtual void Landed(const FHitResult& Hit) override;

	FTimerHandle jumpTimerHandle;

	UPROPERTY(EditAnywhere)
		float jumpingCool;

	UPROPERTY()
		bool bJumping = false;
	
	UFUNCTION()
		void LandingEvent();

	UPROPERTY(EditAnywhere)
		int32 speedValue;

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void SetActionState(const EActionState state) override;

	class UEquipmentComponent* GetEquipmentComp() { return equipmentComp; }

	class UChildActorComponent* GetWeaponChildActor() { return WeaponChild; }
	class UChildActorComponent* GetBowChildActor() { return BowChild; }

	class UInventoryComponent* GetInventoryComp() { return inventoryComp; }

protected:

	virtual void PostInitializeComponents() override;

	void PresedRunStart();
	void PresedRunStop();

	void PresedRoll();

	void PresedAttack();
};
