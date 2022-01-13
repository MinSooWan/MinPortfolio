// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ChildActorComponent.h"
#include "00_Character/00_Player/BaseCharacter.h"
#include "Components/ChildActorComponent.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "01_Item/ItemActor.h"
#include "01_Item/00_Weapon/WeaponBaseActor.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "01_Item/ItemType.h"
#include "00_Character/99_Component/InventoryComponent.h"
#include "01_Item/01_Material/MaterialBaseActor.h"
#include "Components/WidgetComponent.h"
#include "00_Character/99_Component/ToolComponent.h"

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

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

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

	PlayerInputComponent->BindAction("PickUp", EInputEvent::IE_Pressed, this, &APlayerCharacter::PresedPickUp);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerCharacter::Jump()
{
	if ((actionState == EActionState::NORMAL || actionState == EActionState::RUN) && bJumping == false) {
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
	SetActionState(EActionState::NORMAL);
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
		break;
	case EActionState::ROLL:
		GetMesh()->GetAnimInstance()->Montage_Play(GetEquipmentComp()->GetWeaponActor()->GetItemInfo<FWeapon>()->rollMontage);
		break;
	case EActionState::JUMP:
		break;
	default:
		break;
	}
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	OnActorBeginOverlap.AddDynamic(this, &APlayerCharacter::OnActorBeginOverlapEvent);
	OnActorEndOverlap.AddDynamic(this, &APlayerCharacter::OnActorEndOverlapEvent);
}

void APlayerCharacter::PresedRunStart()
{
	SetActionState(EActionState::RUN);
}

void APlayerCharacter::PresedRunStop()
{
	SetActionState(EActionState::NORMAL);
}

void APlayerCharacter::PresedRoll()
{
	if (actionState != EActionState::ROLL && actionState != EActionState::JUMP) {
		SetActionState(EActionState::ROLL);
	}
}

void APlayerCharacter::PresedAttack()
{
	if (!GetEquipmentComp()->GetWeaponActor()->GetItemCode().IsEqual("item_Equipment_NoWeapon")) {
		GetMesh()->GetAnimInstance()->Montage_Play(Cast<AWeaponBaseActor>(GetEquipmentComp()->GetWeaponActor())->GetItemInfo<FWeapon>()->attackMontage);
	}
}

void APlayerCharacter::PresedPickUp()
{

	if (overlapMaterial != nullptr) {
		GetMesh()->GetAnimInstance()->Montage_Play(Cast<AMaterialBaseActor>(overlapMaterial)->GetPickUpMontage());
		inventoryComp->AddItem(overlapMaterial);
		overlapMaterial = nullptr;
	}
}

void APlayerCharacter::OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA<AMaterialBaseActor>() && OtherActor->IsValidLowLevel()) {
		Cast<AMaterialBaseActor>(OtherActor)->GetPickUpWidget()->SetVisibility(true);

		overlapMaterial = OtherActor;
	}
}

void APlayerCharacter::OnActorEndOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	if (overlapMaterial == OtherActor && OtherActor->IsValidLowLevel() && overlapMaterial->IsValidLowLevel()) {
		Cast<AMaterialBaseActor>(OtherActor)->GetPickUpWidget()->SetVisibility(false);

		overlapMaterial = nullptr;
	}
}
