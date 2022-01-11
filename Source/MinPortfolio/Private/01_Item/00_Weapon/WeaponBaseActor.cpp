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

void AWeaponBaseActor::OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{

	if (OtherActor != nullptr && hitArray.Contains(OtherActor) == false) {
		hitArray.Emplace(OtherActor);

		FHitResult hit;

		TArray<TEnumAsByte<EObjectTypeQuery>> objectType;
		objectType.Emplace(ECC_GameTraceChannel2);

		if (UKismetSystemLibrary::LineTraceSingleForObjects(this, GetActorLocation(), OtherActor->GetActorLocation(), objectType, false,
			TArray<AActor*>(), EDrawDebugTrace::ForDuration, hit, true)) {
			UGameplayStatics::SpawnEmitterAtLocation(this, GetItemInfo<FWeapon>()->AttackParticle, hit.Location, FRotator::ZeroRotator, true);
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
			if (player->GetEquipmentComp()->GetWeaponActor()->GetItemInfo<FWeapon>()->item_Code.IsEqual("item_Equipment_NoWeapon")) {
				ItemChange(player, info);
			}
			else {
				if (player->GetEquipmentComp()->GetWeaponActor()->GetItemInfo<FWeapon>()->item_Code.IsEqual(info->item_Code)) {
					RemoveStat(player, info->equipmentStat);
					ItemChange_Default(player, player->GetEquipmentComp()->GetDefaultWeaponActor()->GetItemInfo<FWeapon>());
				}
				else {
					RemoveStat(player, player->GetEquipmentComp()->GetWeaponActor()->GetItemInfo<FWeapon>()->equipmentStat);
					ItemChange(player, info);
				}
			}
		}
	}

}

AWeaponBaseActor::AWeaponBaseActor()
{
	PrimaryActorTick.bCanEverTick = false;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));

	RootComponent = staticMesh;

	staticMesh->SetGenerateOverlapEvents(true);
	staticMesh->SetCollisionProfileName("NoCollision");

}

void AWeaponBaseActor::ItemChange(APlayerCharacter* player, const FWeapon* info)
{
	Super::ItemChange(player, info);

	auto weapon = player->GetWeaponChildActor()->GetChildActor();

	if (weapon != nullptr) {
		player->GetEquipmentComp()->GetWeaponActor()->Destroy();

		AItemActor* spawnItem = GetWorld()->SpawnActor<AItemActor>(info->itemActorClass);
		player->GetEquipmentComp()->SetWeaponActor(*info, spawnItem);

		player->GetWeaponChildActor()->SetChildActorClass(info->itemActorClass);
		Cast<AWeaponBaseActor>(weapon)->GetStaticMesh()->SetStaticMesh(info->mesh);

		player->GetMesh()->SetAnimInstanceClass(info->weaponAnimationBP->GetAnimBlueprintGeneratedClass());
		AddStat(player, info->equipmentStat);
	}
}

void AWeaponBaseActor::ItemChange_Default(APlayerCharacter* player, const FWeapon* info)
{
	Super::ItemChange(player, info);

	AActor* weapon = player->GetWeaponChildActor()->GetChildActor();

	if (weapon != nullptr) {
		if (player->GetEquipmentComp()->GetWeaponActor() != nullptr) { 
			player->GetEquipmentComp()->GetWeaponActor()->Destroy();
		}

		player->GetEquipmentComp()->SetWeaponActor(*info, player->GetEquipmentComp()->GetDefaultWeaponActor());

		player->GetWeaponChildActor()->SetChildActorClass(info->itemActorClass);
		Cast<AWeaponBaseActor>(weapon)->GetStaticMesh()->SetStaticMesh(info->mesh);

		player->GetMesh()->SetAnimInstanceClass(info->weaponAnimationBP->GetAnimBlueprintGeneratedClass());

	}
}