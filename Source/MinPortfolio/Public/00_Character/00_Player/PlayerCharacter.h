// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/00_Player/BaseCharacter.h"
#include "00_Character/99_Component/InventoryComponent.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLoadTransform, FVector, valLoc, FRotator, valRot);

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

protected:
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

protected:
	// APawn interface
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UInventoryComponent* inventoryComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UEquipmentComponent* equipmentComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UToolComponent* toolComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class USkillComponent* skillComp;

	UPROPERTY(VisibleAnywhere)
		class UChildActorComponent* WeaponChild;
	UPROPERTY(VisibleAnywhere)
		class UChildActorComponent* DoubleSwordChild;
	UPROPERTY(VisibleAnywhere)
		class UChildActorComponent* ToolChild;

	/*
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class USceneCaptureComponent2D* sceneCapture;
	*/
	
	void InitStat();
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		int32 targetNum;

public:

	UFUNCTION(BlueprintCallable)
		void targetChange_right();

	UFUNCTION()
		void TargetChange_Left();

	virtual void Jump() override;

protected:
	virtual void Landed(const FHitResult& Hit) override;

	UPROPERTY()
		FTimerHandle jumpTimerHandle;
	UPROPERTY()
		FTimerHandle pickUpAnimEndTimerHandle;

	UPROPERTY(EditAnywhere)
		float jumpingCool;

	UPROPERTY()
		bool bJumping = false;
	
	UFUNCTION()
		void LandingEvent();

	UPROPERTY(EditAnywhere)
		int32 speedValue;

	UPROPERTY()
		bool bWeaponEquipped = false;

	UPROPERTY(VisibleAnywhere)
		AActor* overlapMaterial;

	UPROPERTY()
		EActionState TempAction;

	UPROPERTY()
		bool bInputKeyisPad = false;

	UPROPERTY()
		class ATeleportZone* nextLevel;

	UPROPERTY()
		int32 MyGold = 0;

	UPROPERTY()
		class ANPCCharacter* npc;

	UPROPERTY()
		bool bLevelUp = false;

	UPROPERTY()
		class ACombinationActor* Com;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AToolBaseActor> handToolClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AToolBaseActor> axeToolClass;
public:
	UPROPERTY()
		FLoadTransform LoadTransform;

	UPROPERTY()
		bool bContinueAttack = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		TArray<class AMonsterCharacter*> targets;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		AActor* target;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void SetActionState(const EActionState state) override;
	void Battle_SetActionState(const EActionState state);

	class UEquipmentComponent* GetEquipmentComp() { return equipmentComp; }

	class UChildActorComponent* GetWeaponChildActor() { return WeaponChild; }
	class UChildActorComponent* GetToolChildActor() { return ToolChild; }
	class UChildActorComponent* GetDoubleSwordChild() { return DoubleSwordChild; }

	class UInventoryComponent* GetInventoryComp() { return inventoryComp; }

	class UToolComponent* GetToolComp() { return toolComp; }

	class USkillComponent* GetSkillComp() { return skillComp; }

	bool GetWeaponEquipped() { return bWeaponEquipped; }

	void SetWeaponEquipped(bool value) { bWeaponEquipped = value; }

	void SetOverlapmaterial(AActor* value) { overlapMaterial = value; }

	EActionState GetTempAction() { return TempAction; }

	bool GetInputKeyisPad() { return bInputKeyisPad; }
	
	int32 GetMyGold() { return MyGold; }

	class ACombinationActor* GetCom() { return Com; }

	void SetMyGold(int32 value) { MyGold = value; }

	class ATeleportZone* GetNextLevel() { return nextLevel; }

	class ANPCCharacter* GetNpc() { return npc; }

	virtual void NormalActionState(const EActionState state) override;

protected:

	virtual void PostInitializeComponents() override;

public:
	UFUNCTION()
		void PresedRunStart();
	UFUNCTION()
		void PresedRunStop();

	UFUNCTION()
		void PresedRoll();

	UFUNCTION()
		void PresedAttack();

	UFUNCTION()
		void PresedOnMenu();

	UFUNCTION()
		void PressedBattle_Attack();

	UFUNCTION()
		void PressedAnyKey();

	virtual void ActionChange() override;
	virtual void ActionChange(float cool) override;

	virtual void ActionChange_Able() override;
	virtual void ActionChange_Impossible() override;

	virtual void GiveDamage(float Damage) override;
protected:

	UFUNCTION()
		void OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void OnActorEndOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void OnEndAnimation(AActor* temp, EActionState action);

	UFUNCTION()
		void OnNormalEndAnimation(EActionState action);

	UFUNCTION()
		void LoadLocationEvent(FVector val, FRotator valrot);

	UFUNCTION()
		void OnEndDieAnimation();
};