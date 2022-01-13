// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/02_Tool/ToolBaseActor.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/ToolComponent.h"
#include "01_Item/ItemType.h"
#include "01_Item/ItemActor.h"
#include "Components/ChildActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

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
			player->GetToolComp()->SetToolActor(Cast<AItemActor>(player->GetToolChildActor()->GetChildActor()));
			Cast<AToolBaseActor>(player->GetToolChildActor()->GetChildActor())->GetStaticMesh()->SetStaticMesh(staticMesh->GetStaticMesh());

			player->GetMesh()->SetAnimInstanceClass(item->GetItemInfo<FGatheringTool>()->weaponAnimationBP->GetAnimBlueprintGeneratedClass());
		}
	}
}
