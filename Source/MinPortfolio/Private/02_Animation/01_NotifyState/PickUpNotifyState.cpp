// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Animation/01_NotifyState/PickUpNotifyState.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/ToolComponent.h"
#include "01_Item/ItemType.h"
#include "01_Item/02_Tool/ToolBaseActor.h"

void UPickUpNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp != nullptr) {
		owner = MeshComp->GetOwner<APlayerCharacter>();

		if (owner != nullptr) {
			if (!Cast<AToolBaseActor>(owner->GetToolComp()->GetToolActor())->GetItemCode().IsEqual("item_tool_noTool")) {
				Cast<AToolBaseActor>(owner->GetToolComp()->GetToolActor())->GetStaticMesh()->SetCollisionProfileName("Tool");
			}
		}
	}
}

void UPickUpNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (owner != nullptr) {
		Cast<AToolBaseActor>(owner->GetToolComp()->GetToolActor())->GetStaticMesh()->SetCollisionProfileName("NoCollision");
		Cast<AToolBaseActor>(owner->GetToolComp()->GetToolActor())->ClearHitArray();
	}
}
