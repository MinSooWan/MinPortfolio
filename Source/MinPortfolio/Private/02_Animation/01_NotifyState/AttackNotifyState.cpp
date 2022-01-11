// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Animation/01_NotifyState/AttackNotifyState.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "01_Item/00_Weapon/WeaponBaseActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp != nullptr) {
		owner = MeshComp->GetOwner<APlayerCharacter>();

		if (owner != nullptr) {
			Cast<AWeaponBaseActor>(owner->GetWeaponChildActor()->GetChildActor())->GetSkeletaMesh()->SetCollisionProfileName(TEXT("Weapon"));
		}
	}
}

void UAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (owner != nullptr) {
		Cast<AWeaponBaseActor>(owner->GetWeaponChildActor()->GetChildActor())->GetSkeletaMesh()->SetCollisionProfileName(TEXT("NoCollision"));
		Cast<AWeaponBaseActor>(owner->GetWeaponChildActor()->GetChildActor())->ClearHitArray();
	}
}
