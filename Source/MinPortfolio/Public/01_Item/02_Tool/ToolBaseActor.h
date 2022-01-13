// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemActor.h"
#include "ToolBaseActor.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API AToolBaseActor : public AItemActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* staticMesh;

	UPROPERTY(EditAnywhere)
		FName SocketName;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* AttackParticle;

	void ToolChange(class APlayerCharacter* player, AItemActor* item);

public:
	class UStaticMeshComponent* GetStaticMesh() { return staticMesh; }
};
