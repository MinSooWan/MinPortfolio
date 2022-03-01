// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/03_Battle_Item/RecoveryConsumeActor.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/BuffComponent.h"
#include "Kismet/GameplayStatics.h"

void ARecoveryConsumeActor::AddOption(EAddOptionsType_RecoveryItem option)
{
	addOption.Add(option);
}

void ARecoveryConsumeActor::UseItem(ABaseCharacter* owner)
{
	Super::UseItem(owner);

	APlayerCharacter* player = Cast<APlayerCharacter>(owner);
	if(player != nullptr)
	{
		player->PlayAnimMontage(GetItemInfo<FRecovery_Consume>()->useItemAnim);

		player->GetStatusComponent()->AddHP(GetItemInfo<FRecovery_Consume>()->recover);

		UGameplayStatics::SpawnEmitterAtLocation(player, GetItemInfo<FRecovery_Consume>()->useParticle, player->GetActorLocation());

		for(auto iter : addOption)
		{
			switch (iter)
			{
			case EAddOptionsType_RecoveryItem::ADD_ATC_TIME:
				player->GetBuffComp()->AddBuffState(EBuffState::GIVE_ATC_UP, 20, 5);
				break;
			case EAddOptionsType_RecoveryItem::ADD_DEF_TIME:
				player->GetBuffComp()->AddBuffState(EBuffState::GIVE_DEF_UP, 20, 5);
				break;
			case EAddOptionsType_RecoveryItem::ADD_DEX_TIME:
				player->GetBuffComp()->AddBuffState(EBuffState::GIVE_DEX_UP, 20, 5);
				break;
			case EAddOptionsType_RecoveryItem::ADD_HP_TIME:
				player->GetBuffComp()->AddBuffState(EBuffState::GIVE_HP_UP, 20, 5);
				break;
			case EAddOptionsType_RecoveryItem::RECOVERY_HP:
				player->GetStatusComponent()->AddHP(GetItemInfo<FRecovery_Consume>()->recover / 10);
				break;
			}
		}
	}
}
