// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/99_Component/SkillComponent.h"
#include "00_Character/00_Player/BaseCharacter.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "04_Skill/SkillBaseActor.h"

// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USkillComponent::AddSkill(AActor* skill)
{
	skills.Emplace(skill);
	skill_infos.Emplace(Cast<ASkillBaseActor>(skill)->GetSkillInfo<FSkill>()->skill_Name);
	skill->SetActorHiddenInGame(true);
}

void USkillComponent::UseSkill(FName skillCode)
{
	if(skillCode != "")
	{
		if (GetOwner<APlayerCharacter>()->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == false) {
			for (auto iter : skills)
			{
				if (Cast<ASkillBaseActor>(iter)->GetSkillInfo<FSkill>()->skill_code.IsEqual(skillCode))
				{
					if (GetOwner<APlayerCharacter>()->target != nullptr) {
						Cast<ASkillBaseActor>(iter)->UseSkill(Cast<ABaseCharacter>(GetOwner<APlayerCharacter>()->target), GetOwner<APlayerCharacter>());
						break;
					}
				}
			}
		}
	}
}

