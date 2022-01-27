// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/01_Monster/MonsterCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AMonsterCharacter::AMonsterCharacter()
{
	GetMesh()->SetCollisionProfileName(TEXT("Monster"));

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetMesh()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	SetGenericTeamId(FGenericTeamId(5));
}

void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
