// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemActor.h"
#include "MaterialBaseActor.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API AMaterialBaseActor : public AItemActor
{
	GENERATED_BODY()	

protected:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class USphereComponent* sphereComp;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UParticleSystemComponent* materialParticle;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UStaticMeshComponent* staticMesh;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* pickUpMontage;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UWidgetComponent* pickUpWidgetComp;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* materialMesh;

public:

	AMaterialBaseActor();

	class USphereComponent* GetSphereComp() { return sphereComp; }
	class UWidgetComponent* GetPickUpWidget() { return pickUpWidgetComp; }
	class UAnimMontage* GetPickUpMontage() { return pickUpMontage; }
	virtual void HiddenMesh() override;
};
