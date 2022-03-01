// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/03_Battle_Item/BattleItemActor.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void ABattleItemActor::AddOption(EAddOptionsType_BattleItem option)
{
	addOption.Add(option);
}

void ABattleItemActor::UseItem(ABaseCharacter* owner)
{
	Super::UseItem(owner);

	APlayerCharacter* player = Cast<APlayerCharacter>(owner);
	if(player != nullptr)
	{
		ABaseCharacter* target = Cast<ABaseCharacter>(player->target);

		if(target != nullptr)
		{
			FTimerHandle animTimerHandel;

			FTimerDelegate endTimeDel = FTimerDelegate::CreateUObject(this, &ABattleItemActor::SpawnPaticle, target);
			GetWorld()->GetTimerManager().SetTimer(animTimerHandel, endTimeDel, 
				owner->PlayAnimMontage(GetItemInfo<FBattle_Consume>()->useItemAnim) , false);
		}
	}
}

void ABattleItemActor::SpawnPaticle(ABaseCharacter* target)
{
	target->GetStatusComponent()->SetHP(
		FMath::Clamp(target->GetStatusComponent()->GetHP() - GetItemInfo<FBattle_Consume>()->damage,
			0.f, target->GetStatusComponent()->GetMaxHP()));

	UGameplayStatics::SpawnEmitterAtLocation(target, GetItemInfo<FBattle_Consume>()->useParticle, target->GetActorLocation());

	auto num = FMath::RandRange(0, 101);
	if(num >= 40)
	{
		switch (defaultOption)
		{
		case EAddOptionsType_BattleItem::GIVE_ATC_DOWN:
			target->AddDebuffStateCharacter(EDebuffState::GIVE_ATC_DOWN, 20, 5, EDebuffType::ONE);
			break;
		case EAddOptionsType_BattleItem::GIVE_SLOW:
			target->AddDebuffStateCharacter(EDebuffState::GIVE_SLOW, 20, 5, EDebuffType::ONE);
			break;
		case EAddOptionsType_BattleItem::GIVE_DEF_DOWN:
			target->AddDebuffStateCharacter(EDebuffState::GIVE_DEF_DOWN, 20, 5, EDebuffType::ONE);
			break;
		case EAddOptionsType_BattleItem::GIVE_BURN:
			target->AddDebuffStateCharacter(EDebuffState::GIVE_BURN, 5, 5, EDebuffType::DURATION);
			break;
		case EAddOptionsType_BattleItem::GIVE_DAMAGE:
			target->GetStatusComponent()->SetHP(
				FMath::Clamp(target->GetStatusComponent()->GetHP() - GetItemInfo<FBattle_Consume>()->damage / 10,
					0.f, target->GetStatusComponent()->GetMaxHP()));
			break;
		case EAddOptionsType_BattleItem::GIVE_FROZEN:
			target->AddDebuffStateCharacter(EDebuffState::GIVE_FROZEN, 5, 10, EDebuffType::DURATION);
			break;
		case EAddOptionsType_BattleItem::GIVE_SHOCK:
			target->AddDebuffStateCharacter(EDebuffState::GIVE_SHOCK, 5, 15, EDebuffType::DURATION);
			break;
		}
	}

	if (addOption.Num() > 0) {
		for (auto iter : addOption)
		{
			num = FMath::RandRange(0, 101);

			if (num >= 40) {
				switch (iter)
				{
				case EAddOptionsType_BattleItem::GIVE_ATC_DOWN:
					target->AddDebuffStateCharacter(EDebuffState::GIVE_ATC_DOWN, 20, 5, EDebuffType::ONE);
					break;
				case EAddOptionsType_BattleItem::GIVE_SLOW:
					target->AddDebuffStateCharacter(EDebuffState::GIVE_SLOW, 20, 5, EDebuffType::ONE);
					break;
				case EAddOptionsType_BattleItem::GIVE_DEF_DOWN:
					target->AddDebuffStateCharacter(EDebuffState::GIVE_DEF_DOWN, 20, 5, EDebuffType::ONE);
					break;
				case EAddOptionsType_BattleItem::GIVE_BURN:
					target->AddDebuffStateCharacter(EDebuffState::GIVE_BURN, 5, 5, EDebuffType::DURATION);
					break;
				case EAddOptionsType_BattleItem::GIVE_DAMAGE:
					target->GetStatusComponent()->SetHP(
						FMath::Clamp(target->GetStatusComponent()->GetHP() - GetItemInfo<FBattle_Consume>()->damage / 10,
							0.f, target->GetStatusComponent()->GetMaxHP()));
					break;
				case EAddOptionsType_BattleItem::GIVE_FROZEN:
					target->AddDebuffStateCharacter(EDebuffState::GIVE_FROZEN, 5, 10, EDebuffType::DURATION);
					break;
				case EAddOptionsType_BattleItem::GIVE_SHOCK:
					target->AddDebuffStateCharacter(EDebuffState::GIVE_SHOCK, 5, 15, EDebuffType::DURATION);
					break;
				}
			}
		}
	}
}
