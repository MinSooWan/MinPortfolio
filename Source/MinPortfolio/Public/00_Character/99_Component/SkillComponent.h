// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Skill/SkillInfomation.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINPORTFOLIO_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		TArray<AActor*> skills;

	TArray<FName> skill_infos;
	TArray<FName> skill_codes;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TArray<AActor*> GetSkills() { return skills; }
	void SetSkills(TArray<AActor*> value) { skills = value; }
	TArray<FName> GetSkillInfos() { return skill_infos; }
	void SetSkillInfos(TArray<FName> value) { skill_infos = value; }
	TArray<FName> GetSkillCodes() { return skill_codes; }
	void SetSkillCodes(TArray<FName> value) { skill_codes = value; }

	UFUNCTION(BlueprintCallable)
		void AddSkill(AActor* skill);

	UFUNCTION(BlueprintCallable)
		void UseSkill(FName skillCode);
};
