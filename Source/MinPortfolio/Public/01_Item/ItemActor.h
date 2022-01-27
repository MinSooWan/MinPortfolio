// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "01_Item/ItemType.h"
#include "ItemActor.generated.h"

UCLASS()
class MINPORTFOLIO_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UDataTable* itemTable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName itemCode;

	UPROPERTY()
		bool bEquipped = false;

	//조합품 여부
	UPROPERTY(EditAnywhere)
		bool bCombined = false;

	UPROPERTY()
		int32 itemCount = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		FIteminfo tempinfo;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	template <typename T>
	const T* GetItemInfo();

	FName GetItemCode() { return itemCode; }

	UFUNCTION(BlueprintCallable)
		virtual void UseItem(class ABaseCharacter* itemOwner) { };

	bool GetEquipped() { return bEquipped; }
	void SetEquipped(bool equipped) { bEquipped = equipped; }

	bool GetCombined() { return bCombined; }
	void SetCombined(bool combined) { bCombined = combined; }

	int32 GetItemCount() { return itemCount; }
	void AddItemCount(int32 value) { itemCount += value; }

	virtual void HiddenMesh(){ }
};

template <typename T>
inline const T* AItemActor::GetItemInfo()
{
	if (itemTable != nullptr) {
		return itemTable->FindRow<T>(itemCode, "");
	}
	return nullptr;
}