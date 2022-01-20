// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillBaseActor.generated.h"

UCLASS()
class MINPORTFOLIO_API ASkillBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillBaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UDataTable* SkillTable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName SkillCode;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class USphereComponent* sphereComp;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UParticleSystemComponent* ParticleComp;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UProjectileMovementComponent* ProjectilMovementComp;

public:
	template <typename T>
	const T* GetSkillInfo();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void UseSkill(class ABaseCharacter* target);

};

template <typename T>
inline const T* ASkillBaseActor::GetSkillInfo()
{
	if (SkillTable != nullptr) {
		return SkillTable->FindRow<T>(SkillCode, "");
	}
	return nullptr;
}
