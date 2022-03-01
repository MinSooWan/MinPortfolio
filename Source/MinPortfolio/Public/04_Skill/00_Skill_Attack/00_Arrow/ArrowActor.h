// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArrowActor.generated.h"

UCLASS()
class MINPORTFOLIO_API AArrowActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArrowActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* staticMesh;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* hitParticle;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UParticleSystemComponent* ParticleComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UProjectileMovementComponent* ProjectilMovementComp;

	UPROPERTY(EditAnywhere)
		float lifeTiem;

	UPROPERTY(EditAnywhere)
		float speed;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
		virtual void OnActorHitEvent(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(BlueprintReadOnly)
		float damage;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UStaticMeshComponent* GetStaticMesh() { return staticMesh; }
	class UProjectileMovementComponent* GetProjectilMovementComp() { return ProjectilMovementComp; }

	float GetLifeTiem() { return lifeTiem; }
	float GetSpeed() { return speed; }

	void SetDamage(float value) { damage = value; }
};
