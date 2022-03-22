// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Animation/01_NotifyState/AttackInputNotifyState.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/BattleController.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "01_Item/00_Weapon/WeaponBaseActor.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/03_KeyImage/KeySettingWidget.h"
#include "Components/CanvasPanel.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "97_Task/MoveToTarget_Battle_Task.h"

void UAttackInputNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                          float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp != nullptr) {
		owner = MeshComp->GetOwner<APlayerCharacter>();

		if(owner != nullptr)
		{
			if (nextSection != "End") {
				bContinue = false;

				owner->GetController<ABattleController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Battle()->SetVisibility(ESlateVisibility::Visible);
				owner->GetController<ABattleController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Battle_Skill()->SetVisibility(ESlateVisibility::Hidden);
				owner->GetController<ABattleController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Item()->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

void UAttackInputNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if(owner != nullptr)
	{
		if(owner->bContinueAttack == true)
		{
			bContinue = true;
			owner->GetController<ABattleController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Attack()->SetRenderOpacity(0.3);
		}
	}
}

void UAttackInputNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if(owner != nullptr)
	{
		if(nextSection == "End")
		{
			owner->SetActorRotation((owner->GetStartLocation() - owner->GetActorLocation()).Rotation());
			owner->GetCharacterMovement()->MaxWalkSpeed = 1200;
			owner->SetMoveToStart(true);
		}
		else {
			if (bContinue == true)
			{
				owner->GetMesh()->GetAnimInstance()->Montage_JumpToSection(nextSection);
			}
			else
			{
				owner->GetMesh()->GetAnimInstance()->StopAllMontages(0.1);
				owner->SetActorRotation((owner->GetStartLocation() - owner->GetActorLocation()).Rotation());
				owner->GetCharacterMovement()->MaxWalkSpeed = 1200;

				owner->SetMoveToStart(true);
			}
		}
		
		owner->bContinueAttack = false;
		owner->GetController<ABattleController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Attack()->SetRenderOpacity(1);
		owner->GetController<ABattleController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Battle_Skill()->SetVisibility(ESlateVisibility::Visible);
		owner->GetController<ABattleController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Item()->SetVisibility(ESlateVisibility::Visible);
		owner->GetController<ABattleController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Battle()->SetVisibility(ESlateVisibility::Hidden);
		
	}
}
