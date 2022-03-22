// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Animation/01_NotifyState/GiveDamageNotifyState.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/01_Monster/00_Controller/Battle_AIController.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "01_Item/ItemActor.h"
#include "BehaviorTree/BlackboardComponent.h"

void UGiveDamageNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                         float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp->GetOwner()->IsA<APlayerCharacter>())
	{
		if (bIsDefaultAttack == false) {
			Cast<ABaseCharacter>(MeshComp->GetOwner<APlayerCharacter>()->target)->GiveDamage(damage + MeshComp->GetOwner<ABaseCharacter>()->GetStatusComponent()->GetATC());
		}
		else
		{
			Cast<ABaseCharacter>(MeshComp->GetOwner<APlayerCharacter>()->target)->GiveDamage(MeshComp->GetOwner<APlayerCharacter>()->GetEquipmentComp()->GetWeaponActor()->GetItemStat().ATC
				+ MeshComp->GetOwner<ABaseCharacter>()->GetStatusComponent()->GetATC());
		}
	}
	else if(MeshComp->GetOwner()->IsA<AMonsterCharacter>())
	{
		auto target = MeshComp->GetOwner<AMonsterCharacter>()->GetController<ABattle_AIController>()->GetBlackboardComponent()->GetValueAsObject("Target");
		if (target != nullptr) {
			Cast<ABaseCharacter>(target)->GiveDamage(damage + MeshComp->GetOwner<ABaseCharacter>()->GetStatusComponent()->GetATC());
		}
	}
}
