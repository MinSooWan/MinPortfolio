// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/BattleCharacter.h"

#include "00_Character/99_Component/EquipmentComponent.h"
#include "00_Character/99_Component/InventoryComponent.h"
#include "00_Character/99_Component/SkillComponent.h"
#include "00_Character/99_Component/ToolComponent.h"
#include "01_Item/ItemActor.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#define ORIGINAL_WALK_SPPED 600;

ABattleCharacter::ABattleCharacter()
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
	/*
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
	*/
}

void ABattleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bMoveToTarget == true)
	{
		targetLocation = target->GetActorLocation() - GetActorLocation();
		//UKismetSystemLibrary::PrintString(this, targetLocation.ToString());
		if (target->GetDistanceTo(this) <= 150)
		{
			bMoveToTarget = false;
			Battle_SetActionState(EActionState::ATTACK);
		}
		else {
			AddMovementInput(targetLocation);
		}

		//GetMovementComponent()->Velocity = (target->GetActorLocation() - GetActorLocation());
	}
}

void ABattleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	UKismetSystemLibrary::PrintString(this, "1111111111111");
	//Battle_Attack
	PlayerInputComponent->BindAction("Battle_Attack", EInputEvent::IE_Pressed, this, &ABattleCharacter::PressedBattle_Attack);


}

void ABattleCharacter::PressedBattle_Attack()
{
	UKismetSystemLibrary::PrintString(this, "22222222222222");
	if (target != nullptr)
	{
		UKismetSystemLibrary::PrintString(this, "3333333333333");
		if (!equipmentComp->GetWeaponActor()->GetItemInfo<FWeapon>()->item_Code.IsEqual("item_Equipment_NoWeapon")) {
			if (actionState == EActionState::ATTACK)
			{
				bContinueAttack = true;
			}
			else {
				bMoveToTarget = true;
			}
			//SetActorLocation(target->GetActorLocation());
		}
	}
}
