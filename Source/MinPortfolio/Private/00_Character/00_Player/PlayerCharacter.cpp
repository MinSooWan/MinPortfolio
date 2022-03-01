// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/PlayerCharacter.h"

#include "AIController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ChildActorComponent.h"
#include "00_Character/00_Player/BaseCharacter.h"
#include "00_Character/00_Player/00_Controller/BattleController.h"
#include "Components/ChildActorComponent.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "01_Item/ItemActor.h"
#include "01_Item/00_Weapon/WeaponBaseActor.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/01_Monster/00_Controller/Battle_AIController.h"
#include "01_Item/ItemType.h"
#include "00_Character/99_Component/InventoryComponent.h"
#include "00_Character/99_Component/SkillComponent.h"
#include "01_Item/01_Material/MaterialBaseActor.h"
#include "Components/WidgetComponent.h"
#include "00_Character/99_Component/ToolComponent.h"
#include "01_Item/00_Equipment/ArmorBaseActor.h"
#include "01_Item/00_Equipment/ShoesBaseActor.h"
#include "01_Item/01_Material/MaterialBaseActor.h"
#include "01_Item/02_Tool/ToolBaseActor.h"
#include "01_Item/03_Battle_Item/BattleItemActor.h"
#include "01_Item/03_Battle_Item/RecoveryConsumeActor.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/03_KeyImage/KeySettingWidget.h"
#include "04_Skill/SkillBaseActor.h"
#include "96_Save/BattleSaveGame.h"
#include "98_Instance/MyGameInstance.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "97_Task/CharacterTurnGameplayTask.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CanvasPanel.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/KismetInputLibrary.h"
#include "97_Task/MoveToTarget_Battle_Task.h"

#define ORIGINAL_WALK_SPPED 600;

APlayerCharacter::APlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = ORIGINAL_WALK_SPPED;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	equipmentComp = CreateDefaultSubobject<UEquipmentComponent>(TEXT("equipmentComp"));

	WeaponChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("weapon"));
	WeaponChild->SetupAttachment(GetMesh(), "hand_r_weapon");

	inventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("inventoryComp"));

	GetMesh()->SetCollisionProfileName(TEXT("Player"));

	toolComp = CreateDefaultSubobject<UToolComponent>(TEXT("toolComp"));

	ToolChild = CreateDefaultSubobject< UChildActorComponent>(TEXT("tool"));
	ToolChild->SetupAttachment(GetMesh(), "hand_r_weapon");

	skillComp = CreateDefaultSubobject<USkillComponent>(TEXT("skillComp"));

	DoubleSwordChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("doubleSword"));
	DoubleSwordChild->SetupAttachment(GetMesh(), "hand_l_double");

	DoubleSwordChild->SetVisibility(false);

	SetGenericTeamId(FGenericTeamId(4));

	/*
	sceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("sceneCapture"));
	sceneCapture->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
	*/
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

/*
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	/*
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &APlayerCharacter::PresedRunStart);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &APlayerCharacter::PresedRunStop);

	PlayerInputComponent->BindAction("Roll", EInputEvent::IE_Pressed, this, &APlayerCharacter::PresedRoll);

	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &APlayerCharacter::PresedAttack);

	PlayerInputComponent->BindAction("OnMenu", EInputEvent::IE_Pressed, this, &APlayerCharacter::PresedOnMenu);
	
}
*/

void APlayerCharacter::InitStat()
{
	statComp->SetHP(GetGameInstance<UMyGameInstance>()->Getstat().HP);
	statComp->SetATC(GetGameInstance<UMyGameInstance>()->Getstat().ATC);
	statComp->SetDEF(GetGameInstance<UMyGameInstance>()->Getstat().DEF);
	statComp->SetDEX(GetGameInstance<UMyGameInstance>()->Getstat().DEX);
	statComp->SetMaxHP(GetGameInstance<UMyGameInstance>()->Getstat().MaxHP);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(GetController()->IsA<ACustomController>())
	{
		//UKismetSystemLibrary::PrintString(this, "This CustomController");
		statComp->StatusInit();

		if(GetGameInstance<UMyGameInstance>()->GetStartGame() == false)
		{
			
			equipmentComp->EquipmentItemAddToInven();
			GetGameInstance<UMyGameInstance>()->SetStartGame(true);
		}
		else 
		{
			//위치
			if (!GetGameInstance<UMyGameInstance>()->GetPlayerLocation().IsZero()) {
				LoadTransform.Broadcast(GetGameInstance<UMyGameInstance>()->GetPlayerLocation(), GetGameInstance<UMyGameInstance>()->GetPlayerRotation());
			}

			
			//인벤
			for (auto i = 0; i < GetGameInstance<UMyGameInstance>()->GetInven().Num(); i++)
			{
				auto item = GetWorld()->SpawnActor<AItemActor>(GetGameInstance<UMyGameInstance>()->GetInven()[i]);
				item->SetActorHiddenInGame(true);
				
				switch (item->GetItemInfo<FIteminfo>()->item_Type)
				{
				case EItemType::BATTLE_ITEM:
					if (item->GetItemInfo<FBattleItem>()->battleItemType == EBattleItemType::BATTLE_CONSUME) {
						for (auto iter : GetGameInstance<UMyGameInstance>()->haveItems[i].battleItemAddOptions)
						{
							Cast<ABattleItemActor>(item)->AddOption(iter);
						}
					}
					else
					{
						for (auto iter : GetGameInstance<UMyGameInstance>()->haveItems[i].recoveryItemAddOptions)
						{
							Cast<ARecoveryConsumeActor>(item)->AddOption(iter);
						}
					}
					break;
				case EItemType::EQUIPMENT:
					if (item->GetItemInfo<FEquipment>()->equipment_Type == EEquipmentType::WEAPON)
					{
						for (auto iter : GetGameInstance<UMyGameInstance>()->haveItems[i].weaponAddOption)
						{
							Cast<AWeaponBaseActor>(item)->AddOption_Weapon(iter);
						}
					}
					else
					{
						for (auto iter : GetGameInstance<UMyGameInstance>()->haveItems[i].armorAddOption)
						{
							Cast<AArmorBaseActor>(item)->AddOption(iter);
						}
					}

					item->SetItemStat(GetGameInstance<UMyGameInstance>()->haveItems[i].stat);
					break;
				case EItemType::MATERIAL:
					for (auto iter : GetGameInstance<UMyGameInstance>()->haveItems[i].materialAddOptions)
					{
						Cast<AMaterialBaseActor>(item)->AddOption(iter);
					}
					item->SetItemStat(GetGameInstance<UMyGameInstance>()->haveItems[i].stat);
					break;
				}

				inventoryComp->AddItem(item);
			}

			//장비
			for (auto i = 0; i < inventoryComp->GetItemArray().Num(); i++)
			{
				AItemActor* item = Cast<AItemActor>(inventoryComp->GetItemArray()[i]);
				if (item->GetItemInfo<FIteminfo>()->item_Type == EItemType::EQUIPMENT)
				{
					if (GetGameInstance<UMyGameInstance>()->GetHaveItems()[i].bEquipped == true)
					{
						item->UseItem(this);
					}
				}
			}
		}
	}
	else if(GetController()->IsA<ABattleController>())
	{
		toolComp->ToolCompInit();
		equipmentComp->EquipmentCompInit();

		//UKismetSystemLibrary::PrintString(this, "This BattleController");
		if(GetGameInstance<UMyGameInstance>()->GetWeapon() != nullptr)
		{
			//위치
			startLocation = GetActorLocation();

			Battle_SetActionState(EActionState::NORMAL);

			//인벤
			for (auto i = 0; i < GetGameInstance<UMyGameInstance>()->GetInven().Num(); i++)
			{
				auto item = GetWorld()->SpawnActor<AItemActor>(GetGameInstance<UMyGameInstance>()->GetInven()[i]);
				item->SetActorHiddenInGame(true);
;
				switch (item->GetItemInfo<FIteminfo>()->item_Type)
				{
				case EItemType::BATTLE_ITEM:
					if (item->GetItemInfo<FBattleItem>()->battleItemType == EBattleItemType::BATTLE_CONSUME) {
						 for(auto iter : GetGameInstance<UMyGameInstance>()->haveItems[i].battleItemAddOptions)
						 {
							 Cast<ABattleItemActor>(item)->AddOption(iter);
						 }
					}
					else
					{
						for (auto iter : GetGameInstance<UMyGameInstance>()->haveItems[i].recoveryItemAddOptions)
						{
							Cast<ARecoveryConsumeActor>(item)->AddOption(iter);
						}
					}
					break;
				case EItemType::EQUIPMENT:
					if(item->GetItemInfo<FEquipment>()->equipment_Type == EEquipmentType::WEAPON)
					{
						for (auto iter : GetGameInstance<UMyGameInstance>()->haveItems[i].weaponAddOption)
						{
							Cast<AWeaponBaseActor>(item)->AddOption_Weapon(iter);
						}
					}
					else
					{
						for (auto iter : GetGameInstance<UMyGameInstance>()->haveItems[i].armorAddOption)
						{
							Cast<AArmorBaseActor>(item)->AddOption(iter);
						}
					}

					item->SetItemStat(GetGameInstance<UMyGameInstance>()->haveItems[i].stat);
					break;
				case EItemType::MATERIAL:
					for (auto iter : GetGameInstance<UMyGameInstance>()->haveItems[i].materialAddOptions)
					{
						Cast<AMaterialBaseActor>(item)->AddOption(iter);
					}

					item->SetItemStat(GetGameInstance<UMyGameInstance>()->haveItems[i].stat);
					break;
				}

				inventoryComp->AddItem(item);
			}

			//장비
			for (auto i = 0; i < inventoryComp->GetItemArray().Num(); i++)
			{
				AItemActor* item = Cast<AItemActor>(inventoryComp->GetItemArray()[i]);
				if(item->GetItemInfo<FIteminfo>()->item_Type == EItemType::EQUIPMENT)
				{
					if(GetGameInstance<UMyGameInstance>()->GetHaveItems()[i].bEquipped == true)
					{
						item->UseItem(this);
						if(item->GetItemInfo<FEquipment>()->equipment_Type == EEquipmentType::WEAPON)
						{
							WeaponChild->SetVisibility(true);
							GetMesh()->SetAnimInstanceClass(item->GetItemInfo<FWeapon>()->weaponAnimationBP->GetAnimBlueprintGeneratedClass());
						}
					}
				}
			}

			//채집 도구
			auto tool = GetWorld()->SpawnActor<AToolBaseActor>(GetGameInstance<UMyGameInstance>()->GetTool());
			if(tool != nullptr)
			{
				tool->UseItem(this);
				ToolChild->SetVisibility(false);
				tool->SetActorHiddenInGame(true);
			}

			/*
			//갑옷
			auto armor = inventoryComp->FindItem();
			if(armor != nullptr)
			{

				armor->UseItem(this);
				armor->SetActorHiddenInGame(true);
			}

			//무기
			auto weapon = GetWorld()->SpawnActor<AWeaponBaseActor>(GetGameInstance<UMyGameInstance>()->GetWeapon());
			if (weapon != nullptr) {

				weapon->UseItem(this);
				WeaponChild->SetVisibility(true);
				if(weapon->GetItemInfo<FWeapon>()->swordType == ESwordType::DOUBLE_SWORD)
				{
					DoubleSwordChild->SetVisibility(true);
				}

				GetMesh()->SetAnimInstanceClass(weapon->GetItemInfo<FWeapon>()->weaponAnimationBP->GetAnimBlueprintGeneratedClass());

				weapon->SetActorHiddenInGame(true);
			}

			//신발
			auto shoes = GetWorld()->SpawnActor<AShoesBaseActor>(GetGameInstance<UMyGameInstance>()->GetShoes());
			if(shoes != nullptr)
			{
				if (GetGameInstance<UMyGameInstance>()->GetShoesAddOption().Num() > 0) {
					for (auto iter : GetGameInstance<UMyGameInstance>()->GetShoesAddOption())
					{
						shoes->AddOption(iter);
					}
				}

				shoes->UseItem(this);
				shoes->SetActorHiddenInGame(true);
			}
			*/

			//몬스터
			//
			int32 cnt = FMath::RandRange(1, 3);
			auto monster = GetWorld()->SpawnActor<AMonsterCharacter>(GetGameInstance<UMyGameInstance>()->GetTarget(),
				GetGameInstance<UMyGameInstance>()->GetTargetPoint()[0]);

			monster->AIControllerClass = monster->GetBattle_Controller();

			monster->SpawnDefaultController();

			monster->GetController<AAIController>()->GetBlackboardComponent()->SetValueAsObject("Target", this);
			monster->GetController<AAIController>()->GetBlackboardComponent()->SetValueAsVector("TargetLocation", GetActorLocation());

			monster->GetStatusComponent()->StatusInit();

			monster->SetActionState(EActionState::RUN);
			monster->GetCharacterMovement()->MaxWalkSpeed = 800;

			target = monster;

			SetActorRotation((target->GetActorLocation() - GetActorLocation()).Rotation());

			targets.Add(monster);
			targetNum = 0;

			//UKismetSystemLibrary::PrintString(this, FString::FromInt(cnt));

			if (cnt > 0) {
				for (int32 i = 1; i < cnt; i++)
				{
					monster = GetWorld()->SpawnActor<AMonsterCharacter>(GetGameInstance<UMyGameInstance>()->GetTarget(),
						GetGameInstance<UMyGameInstance>()->GetTargetPoint()[i]);

					monster->AIControllerClass = monster->GetBattle_Controller();

					monster->SpawnDefaultController();

					monster->GetController<AAIController>()->GetBlackboardComponent()->SetValueAsObject("Target", this);
					monster->GetController<AAIController>()->GetBlackboardComponent()->SetValueAsVector("TargetLocation", GetActorLocation());
					
					monster->GetStatusComponent()->StatusInit();

					monster->SetActionState(EActionState::RUN);
					monster->GetCharacterMovement()->MaxWalkSpeed = 800;

					targets.Add(monster);
				}
			}

			//스킬
			for(auto iter : GetGameInstance<UMyGameInstance>()->GetSkill())
			{
				auto skill = GetWorld()->SpawnActor<ASkillBaseActor>(iter);
				skillComp->AddSkill(skill);
			}

			//스탯
			InitStat();

			//auto FVector(110,160,20)transform = FTransform(FRotator(0,0,-20),);
			FollowCamera->SetRelativeLocation(FVector(110, 180, 20));
			FollowCamera->SetRelativeRotation(FRotator(0, -20,0));

			auto num = FMath::RandRange(3, 5);
			ActionChange(num);
		}
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void APlayerCharacter::targetChange_right()
{
	if (actionState == EActionState::NORMAL && bMoveToTarget == false && bMoveToStatrLocation == false) {
		if (targets.Num() > 1)
		{
			if (targets.Num() - 1 == targetNum)
			{
				targetNum = 0;
				target = targets[targetNum];
			}
			else
			{
				targetNum++;
				target = targets[targetNum];
			}
			UCharacterTurnGameplayTask::CharacterTurnGameplayTask(this, Cast<AMonsterCharacter>(target))->ReadyForActivation();
		}
	}
}

void APlayerCharacter::TargetChange_Left()
{
	if (actionState == EActionState::NORMAL && bMoveToTarget == false && bMoveToStatrLocation == false) {
		if (targets.Num() > 1)
		{
			if (targets.Num() - 1 == targetNum)
			{
				targetNum = 1;
				target = targets[targetNum];
			}
			else if (targetNum == 0)
			{
				targetNum = targets.Num() - 1;
				target = targets[targetNum];
			}
			else
			{
				targetNum--;
				target = targets[targetNum];
			}
			UCharacterTurnGameplayTask::CharacterTurnGameplayTask(this, Cast<AMonsterCharacter>(target))->ReadyForActivation();
		}
	}
}

void APlayerCharacter::Jump()
{
	
	if (bJumping == false && actionState != EActionState::ROLL &&
		actionState != EActionState::ATTACK) {
		TempAction = actionState;
		Super::Jump();
		SetActionState(EActionState::JUMP);
		bJumping = true;
	}
}

void APlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	GetCharacterMovement()->MaxWalkSpeed = speedValue;
	FTimerDelegate endTimeDel = FTimerDelegate::CreateUObject(this, &APlayerCharacter::LandingEvent);

	GetWorld()->GetTimerManager().SetTimer(jumpTimerHandle, endTimeDel, jumpingCool, false);
}

void APlayerCharacter::LandingEvent()
{
	bJumping = false;
	SetActionState(TempAction);
}

float APlayerCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return 0.0f;
}

void APlayerCharacter::SetActionState(const EActionState state)
{
	actionState = state;	

	switch (actionState)
	{
	case EActionState::NORMAL:
		GetCharacterMovement()->MaxWalkSpeed = ORIGINAL_WALK_SPPED;

		break;
	case EActionState::RUN:
		GetCharacterMovement()->MaxWalkSpeed = 800;

		break;
	case EActionState::ATTACK:
		if (!GetMesh()->GetAnimInstance()->IsAnyMontagePlaying()) {
			if (overlapMaterial != nullptr) {
				if (Cast<AMaterialBaseActor>(overlapMaterial)->GetItemInfo<FItemMaterial>()->needTool ==
					GetToolComp()->GetToolActor()->GetItemInfo<FGatheringTool>()->toolType) {

					UGameplayStatics::SpawnEmitterAtLocation(this, Cast<AMaterialBaseActor>(overlapMaterial)->GetPickUpParticle(),
						overlapMaterial->GetActorLocation(), FRotator::ZeroRotator, true);

					auto temp = overlapMaterial;
					Cast<AMaterialBaseActor>(overlapMaterial)->GetSphereComp()->SetCollisionProfileName(TEXT("NoCollision"));

					FTimerDelegate timeDel;
					timeDel.BindUFunction(this, FName("OnEndAnimation"), temp, TempAction);

					GetWorld()->GetTimerManager().SetTimer(pickUpAnimEndTimerHandle, timeDel,
						GetMesh()->GetAnimInstance()->Montage_Play(GetToolComp()->GetToolActor()->GetItemInfo<FGatheringTool>()->useToolAnim),
						false);

					return;
				}
			}

			if (!GetToolComp()->GetToolActor()->GetItemInfo<FIteminfo>()->item_Code.IsEqual("item_Tool_NoTool")) {
				FTimerDelegate timeDel;
				timeDel.BindUFunction(this, FName("OnNormalEndAnimation"), TempAction);

				GetWorld()->GetTimerManager().SetTimer(pickUpAnimEndTimerHandle, timeDel,
					GetMesh()->GetAnimInstance()->Montage_Play(GetToolComp()->GetToolActor()->GetItemInfo<FGatheringTool>()->useToolAnim),
					false);
			}
			else
			{
				SetActionState(EActionState::NORMAL);
			}
		}
		break;
	case EActionState::ROLL:
		GetMesh()->GetAnimInstance()->Montage_Play(GetToolComp()->GetToolActor()->GetItemInfo<FGatheringTool>()->rollMontage);

		break;
	case EActionState::JUMP:
		break;
	default:
		break;
	}
}

void APlayerCharacter::Battle_SetActionState(const EActionState state)
{
	actionState = state;

	FTimerDelegate timeDel;
	timeDel.BindUFunction(this, FName("ActionChange_Impossible"));

	switch (actionState)
	{
	case EActionState::NORMAL:
		GetCharacterMovement()->MaxWalkSpeed = 800;

		break;
	case EActionState::ATTACK:

		GetWorld()->GetTimerManager().SetTimer(ImpossibleAction, timeDel,GetMesh()->GetAnimInstance()->Montage_Play(Cast<AWeaponBaseActor>(GetWeaponChildActor()->GetChildActor())->GetItemInfo<FWeapon>()->attackMontage), false);

		break;
	case EActionState::MOVE:

		break;
	}
}

void APlayerCharacter::NormalActionState(const EActionState state)
{
	Super::NormalActionState(state);
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	OnActorBeginOverlap.AddDynamic(this, &APlayerCharacter::OnActorBeginOverlapEvent);
	OnActorEndOverlap.AddDynamic(this, &APlayerCharacter::OnActorEndOverlapEvent);
	LoadTransform.AddDynamic(this, &APlayerCharacter::LoadLocationEvent);
}

void APlayerCharacter::PresedRunStart()
{
	TempAction = EActionState::RUN;
	if (actionState != EActionState::ATTACK && actionState != EActionState::JUMP && actionState != EActionState::ROLL) {
		SetActionState(EActionState::RUN);
	}
}

void APlayerCharacter::PresedRunStop()
{
	TempAction = EActionState::NORMAL;
	if (actionState != EActionState::ATTACK && actionState != EActionState::JUMP && actionState != EActionState::ROLL) {
		SetActionState(EActionState::NORMAL);
	}
}

void APlayerCharacter::PresedRoll()
{
	if (actionState != EActionState::ROLL && actionState != EActionState::JUMP && actionState != EActionState::ATTACK && 
		!GetMovementComponent()->IsFalling()) {
		TempAction = actionState;
		SetActionState(EActionState::ROLL);
	}
}

void APlayerCharacter::PresedAttack()
{
	if (actionState != EActionState::ROLL && actionState != EActionState::JUMP && !GetMovementComponent()->IsFalling()) {
		TempAction = actionState;
		SetActionState(EActionState::ATTACK);
	}
}

void APlayerCharacter::PresedOnMenu()
{
	GetController<ACustomController>()->GetMainWidget()->OnMenuWidget.Broadcast();
}

void APlayerCharacter::PressedBattle_Attack()
{
	if (target != nullptr)
	{
		if (Cast<AMonsterCharacter>(target)->GetBattleState() == EActionState::NORMAL) {
			if (bAbleAction == true) {
				if (bMoveToStatrLocation == false) {
					if (equipmentComp->GetWeaponActor()->GetItemInfo<FWeapon>()->weaponType != EWeaponType::WAND && equipmentComp->GetWeaponActor()->GetItemInfo<FWeapon>()->weaponType != EWeaponType::BOW) {
						if (actionState == EActionState::ATTACK)
						{
							bContinueAttack = true;
						}
						else {
							NormalActionState(EActionState::ATTACK);
							GetCharacterMovement()->MaxWalkSpeed = 1200;
							bMoveToTarget = true;

							UMoveToTarget_Battle_Task::MoveToTarget_Battle_Task(this, Cast<AMonsterCharacter>(target), bMoveToTarget, bMoveToStatrLocation,
								Cast<AWeaponBaseActor>(GetWeaponChildActor()->GetChildActor())->GetItemInfo<FWeapon>()->attackMontage)->ReadyForActivation();
						}
						//SetActorLocation(target->GetActorLocation());
					}
					else
					{
						if (actionState == EActionState::NORMAL) {

							//NormalActionState(EActionState::ATTACK);

							FTimerDelegate timeDel;
							timeDel.BindUFunction(this, "NormalActionState", EActionState::NORMAL);

							//GetWorld()->GetTimerManager().SetTimer(ImpossibleAction, timeDel, GetMesh()->GetAnimInstance()->Montage_Play(Cast<AWeaponBaseActor>(GetWeaponChildActor()->GetChildActor())->GetItemInfo<FWeapon>()->attackMontage), false);
						}
					}
				}
			}
			else if (bAbleAction == false && actionState == EActionState::ATTACK)
			{
				bContinueAttack = true;
			}
		}
	}
}

void APlayerCharacter::PressedAnyKey()
{
	GetController<ACustomController>()->GetMainWidget()->ChangeKeyMode.Broadcast(UKismetInputLibrary::Key_IsGamepadKey(EKeys::AnyKey));
}

void APlayerCharacter::ActionChange()
{
	Super::ActionChange();
}

void APlayerCharacter::ActionChange(float cool)
{
	Super::ActionChange(cool);

	FTimerDelegate timeDel;
	timeDel.BindUFunction(this, FName("ActionChange_Able"));

	GetWorld()->GetTimerManager().SetTimer(AbleAction, timeDel, cool, false);
}

void APlayerCharacter::ActionChange_Able()
{
	Super::ActionChange_Able();

	GetController<ABattleController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Battle()->SetVisibility(ESlateVisibility::Visible);
}

void APlayerCharacter::ActionChange_Impossible()
{
	Super::ActionChange_Impossible();

	GetController<ABattleController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Battle()->SetVisibility(ESlateVisibility::Hidden);

	FTimerDelegate timeDel;
	timeDel.BindUFunction(this, FName("ActionChange_Able"));

	GetWorld()->GetTimerManager().SetTimer(ImpossibleAction, timeDel, 9, false);
}

void APlayerCharacter::OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	if (GetController()->IsA<ACustomController>()) {
		if (OtherActor->IsA<AMaterialBaseActor>() && OtherActor->IsValidLowLevel()) {
			Cast<AMaterialBaseActor>(OtherActor)->GetPickUpWidget()->SetVisibility(true);

			overlapMaterial = OtherActor;
		}

		if (target == nullptr) {
			if (OtherActor->IsA<AMonsterCharacter>() && OtherActor->IsValidLowLevel())
			{
				target = OtherActor;
				GetGameInstance<UMyGameInstance>()->SetTarget(Cast<AMonsterCharacter>(OtherActor)->GetClass());
				Cast<AMonsterCharacter>(target)->GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
				Cast<AMonsterCharacter>(target)->GetMesh()->SetCollisionProfileName("NoCollision");

				GetGameInstance<UMyGameInstance>()->monInfo.monLoc = Cast<AMonsterCharacter>(target)->GetHomeLocation();
				GetGameInstance<UMyGameInstance>()->monInfo.monHp = Cast<AMonsterCharacter>(target)->GetStatusComponent()->GetHP();

				GetController<ACustomController>()->ChangeBattleLevel();
			}
		}
	}
}

void APlayerCharacter::OnActorEndOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	if (overlapMaterial == OtherActor && OtherActor->IsValidLowLevel() && overlapMaterial->IsValidLowLevel()) {
		Cast<AMaterialBaseActor>(OtherActor)->GetPickUpWidget()->SetVisibility(false);

		overlapMaterial = nullptr;
	}
}

void APlayerCharacter::OnEndAnimation(AActor* temp, EActionState action)
{
	if(Cast<AMaterialBaseActor>(temp)->GetStaticMesh() != nullptr)
	{
		Cast<AMaterialBaseActor>(temp)->GetStaticMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	}
	inventoryComp->AddItem(temp);
	overlapMaterial = nullptr;
	SetActionState(action);
}

void APlayerCharacter::OnNormalEndAnimation(EActionState action)
{	
	SetActionState(action);
}

void APlayerCharacter::LoadLocationEvent(FVector val, FRotator valrot)
{
	SetActorLocation(val);
	SetActorRotation(valrot);
}
