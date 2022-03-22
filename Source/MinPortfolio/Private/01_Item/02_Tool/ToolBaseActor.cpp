// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/02_Tool/ToolBaseActor.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/BattleController.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/99_Component/ToolComponent.h"
#include "01_Item/ItemType.h"
#include "Components/ChildActorComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "01_Item/01_Material/MaterialBaseActor.h"
#include "03_Widget/MainWidget.h"
#include "98_Instance/MyGameInstance.h"
#include "99_GameMode/MainGameModeBase.h"

void AToolBaseActor::ToolChange(APlayerCharacter* player, AItemActor* item)
{
	auto tool = player->GetToolComp()->GetToolActor();

	if (tool != nullptr && item != nullptr) {

		auto info = item->GetItemInfo<FIteminfo>();

		if (info != nullptr) {
			player->GetToolComp()->GetToolActor()->Destroy();

			player->GetToolComp()->SetToolActor(item);

			player->GetToolChildActor()->AttachToComponent(player->GetMesh(),
				FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true),
				SocketName);

			player->GetToolChildActor()->SetChildActorClass(info->itemActorClass);
			Cast<AToolBaseActor>(player->GetToolChildActor()->GetChildActor())->GetStaticMesh()->SetStaticMesh(staticMesh->GetStaticMesh());

			player->GetMesh()->SetAnimInstanceClass(item->GetItemInfo<FGatheringTool>()->weaponAnimationBP->GetAnimBlueprintGeneratedClass());

			Cast<AToolBaseActor>(player->GetToolComp()->GetToolActor())->playerOwner = player;
		}
	}
}

void AToolBaseActor::UseItem(ABaseCharacter* owner)
{
	if (owner != nullptr) {
		APlayerCharacter* player = Cast<APlayerCharacter>(owner);
		const FGatheringTool* info = GetItemInfo<FGatheringTool>();

		if (info != nullptr) {
			AItemActor* spawnItem = Cast<AItemActor>(this);

			if (player->GetToolComp()->GetToolActor() != nullptr) {
				if (!player->GetToolComp()->GetToolActor()->GetItemInfo<FIteminfo>()->item_Code.IsEqual(info->item_Code)) {
					ToolChange(player, spawnItem);
				}
			}
			spawnItem->Destroy();
		}
	}
}

void AToolBaseActor::OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor != nullptr && hitArray.Contains(OtherActor) == false) {
		hitArray.Emplace(OtherActor);
		
		if (OtherActor->IsA<AItemActor>()) {
			

		}
		else if(OtherActor->IsA<AMonsterCharacter>()) {
			//UKismetSystemLibrary::PrintString(this, "2222222222");
			if(playerOwner != nullptr)
			{
				GetGameInstance<UMyGameInstance>()->SetTarget(Cast<AMonsterCharacter>(OtherActor)->GetClass());
				playerOwner->GetController<ACustomController>()->ChangeBattleLevel();
			}
		}
	}
}

AToolBaseActor::AToolBaseActor()
{
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));
	staticMesh->SetCollisionProfileName("NoCollision");
	OnActorBeginOverlap.AddDynamic(this, &AToolBaseActor::OnActorBeginOverlapEvent);

	RootComponent = staticMesh;
}
