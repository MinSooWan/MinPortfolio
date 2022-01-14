// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/02_Tool/ToolBaseActor.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/ToolComponent.h"
#include "01_Item/ItemType.h"
#include "Components/ChildActorComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "01_Item/01_Material/MaterialBaseActor.h"

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

void AToolBaseActor::UseItem(ABaseCharacter* target)
{
	if (target != nullptr) {
		APlayerCharacter* player = Cast<APlayerCharacter>(target);
		const FGatheringTool* info = GetItemInfo<FGatheringTool>();

		if (info != nullptr) {
			AItemActor* spawnItem = GetWorld()->SpawnActor<AItemActor>(info->itemActorClass);

			if (!player->GetToolComp()->GetToolActor()->GetItemInfo<FGatheringTool>()->item_Code.IsEqual(info->item_Code)) {
				ToolChange(player, spawnItem);
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
		else {
			UE_LOG(LogTemp, Log, TEXT("111111111111111111"));
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
