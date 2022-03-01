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

	UPROPERTY(EditAnywhere)
		class UParticleSystem* pickUpParticle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<EAddOptionsType_Material> addOption;
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		virtual void AddOption(EAddOptionsType_Material option);

	AMaterialBaseActor();

	class UStaticMeshComponent* GetStaticMesh() { return materialMesh; };
	class USphereComponent* GetSphereComp() { return sphereComp; }
	class UWidgetComponent* GetPickUpWidget() { return pickUpWidgetComp; }
	class UAnimMontage* GetPickUpMontage() { return pickUpMontage; }
	virtual void HiddenMesh() override;

	class UParticleSystem* GetPickUpParticle() { return pickUpParticle; }

	TArray<EAddOptionsType_Material> GetAddOption() { return addOption; }

	void RandomAddOption();
};
