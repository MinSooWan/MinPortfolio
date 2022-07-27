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

	void ToolChange(class APlayerCharacter* player, AItemActor* item);

	UPROPERTY()
		TArray<AActor*> hitArray;

	UFUNCTION()
		void OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = BPClasses)
		UClass* UseAnim;

public:

	virtual void UseItem(class ABaseCharacter* owner) override;

	AToolBaseActor();

	UPROPERTY()
		class APlayerCharacter* playerOwner;

	class UStaticMeshComponent* GetStaticMesh() { return staticMesh; }

	void ClearHitArray() { hitArray.Empty(); }
};
