// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/00_Weapon/WeaponBaseActor.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "01_Item/ItemType.h"
#include "01_Item/ItemActor.h"
#include "Components/ChildActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void AWeaponBaseActor::OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor != nullptr && hitArray.Contains(OtherActor) == false) {
		hitArray.Emplace(OtherActor);

		FHitResult hit;

		//TArray<TEnumAsByte<EObjectTypeQuery>> objectType;
		//objectType.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel2));
		/*
		UE_LOG(LogTemp, Log, TEXT("111111111"));
		if (UKismetSystemLibrary::LineTraceSingleForObjects(OtherActor, GetActorLocation(), OtherActor->GetActorLocation(), objectType, false,
			TArray<AActor*>(), EDrawDebugTrace::ForDuration, hit, true)) {
			UE_LOG(LogTemp, Log, TEXT("2222222222"));
			UGameplayStatics::SpawnEmitterAtLocation(this, AttackParticle, hit.Location, FRotator::ZeroRotator, true);
		}
		*/

		TArray<TEnumAsByte<EObjectTypeQuery>> objectType;
		objectType.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel2));

		if (UKismetSystemLibrary::LineTraceSingleForObjects(this, GetActorLocation(), OtherActor->GetActorLocation(), objectType, false,
			TArray<AActor*>(), EDrawDebugTrace::ForDuration, hit, true)) {
			UGameplayStatics::SpawnEmitterAtLocation(this, AttackParticle, hit.Location, FRotator::ZeroRotator, true);

		}
	}
}

void AWeaponBaseActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnActorBeginOverlap.AddUniqueDynamic(this, &AWeaponBaseActor::OnActorBeginOverlapEvent);
}

void AWeaponBaseActor::UseItem(class ABaseCharacter* target)
{
	Super::UseItem(target);

	if (target != nullptr) {
		APlayerCharacter* player = Cast<APlayerCharacter>(target);
		const FWeapon* info = GetItemInfo<FWeapon>();

		if (info != nullptr) {
			AItemActor* spawnItem = GetWorld()->SpawnActor<AItemActor>(info->itemActorClass);
			if (player->GetEquipmentComp()->GetWeaponActor()->GetItemInfo<FWeapon>()->item_Code.IsEqual("item_Equipment_NoWeapon")) {
				ItemChange(player, spawnItem->GetItemInfo<FWeapon>(), spawnItem);
			}
			else {
				if (player->GetEquipmentComp()->GetWeaponActor()->GetItemInfo<FWeapon>()->item_Code.IsEqual(info->item_Code)) {
					RemoveStat(player, info->equipmentStat);
					ItemChange_Default(player, player->GetEquipmentComp()->GetDefaultWeaponActor()->GetItemInfo<FWeapon>(), player->GetEquipmentComp()->GetDefaultWeaponActor());
				}
				else {
					RemoveStat(player, player->GetEquipmentComp()->GetWeaponActor()->GetItemInfo<FWeapon>()->equipmentStat);
					ItemChange(player, spawnItem->GetItemInfo<FWeapon>(), spawnItem);
				}
			}

			spawnItem->Destroy();
		}
	}

}

AWeaponBaseActor::AWeaponBaseActor()
{
	

}

void AWeaponBaseActor::ItemChange(APlayerCharacter* player, const FEquipment* info, AItemActor* item)
{
	Super::ItemChange(player, info, item);

	auto weapon = player->GetEquipmentComp()->GetWeaponActor();

	if (weapon != nullptr) {

		player->GetWeaponChildActor()->SetVisibility(true);

		player->GetEquipmentComp()->GetWeaponActor()->Destroy();

		player->GetEquipmentComp()->SetWeaponActor(*info, item);
		

		player->GetWeaponChildActor()->AttachToComponent(player->GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true),
			SocketName);

		player->GetWeaponChildActor()->SetChildActorClass(info->itemActorClass);
		player->GetEquipmentComp()->SetWeaponActor(*info, Cast<AItemActor>(player->GetWeaponChildActor()->GetChildActor()));
		Cast<AEquipmentActor>(player->GetWeaponChildActor()->GetChildActor())->GetStaticMesh()->SetStaticMesh(info->mesh);

		player->GetMesh()->SetAnimInstanceClass(item->GetItemInfo<FWeapon>()->weaponAnimationBP->GetAnimBlueprintGeneratedClass());
		AddStat(player, info->equipmentStat);

		player->SetWeaponEquipped(true);
	}
}

void AWeaponBaseActor::ItemChange_Default(APlayerCharacter* player, const FEquipment* info, AItemActor* item)
{
	Super::ItemChange_Default(player, info, item);

	auto weapon = player->GetEquipmentComp()->GetWeaponActor();

	if (weapon != nullptr) {
		if (player->GetEquipmentComp()->GetWeaponActor() != nullptr) {
			player->GetEquipmentComp()->GetWeaponActor()->Destroy();
		}

		player->GetEquipmentComp()->SetWeaponActor(*info, player->GetEquipmentComp()->GetDefaultWeaponActor());

		player->GetWeaponChildActor()->SetChildActorClass(info->itemActorClass);
		Cast<AEquipmentActor>(player->GetWeaponChildActor()->GetChildActor())->GetStaticMesh()->SetStaticMesh(info->mesh);

		player->GetMesh()->SetAnimInstanceClass(item->GetItemInfo<FWeapon>()->weaponAnimationBP->GetAnimBlueprintGeneratedClass());

		player->SetWeaponEquipped(false);
	}
}