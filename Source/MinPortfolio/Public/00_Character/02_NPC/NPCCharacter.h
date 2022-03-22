// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/00_Player/BaseCharacter.h"
#include "Engine/DataTable.h"
#include "NPCCharacter.generated.h"

UENUM(BlueprintType)
enum class ENPCType : uint8
{
	SHOP,
	REINFORCE,
	TALK
};

USTRUCT(BlueprintType)
struct FShopItemType : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AItemActor> shopItem;
};


/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API ANPCCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ANPCCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class USphereComponent* sphereComp;

	UPROPERTY(EditAnywhere)
		ENPCType npcType;
	  
	UPROPERTY(EditAnywhere, meta = (EditCondition = "npcType == ENPCType::SHOP", EditConditionHides))
		class UDataTable* shopItemTable;

	UPROPERTY(EditAnywhere)
		FString npcName;

public:
	ENPCType GetNpcType() { return npcType; }
	FString GetNpcName() { return npcName; }
	UPROPERTY(meta = (EditCondition = "npcType == ENPCType::SHOP", EditConditionHides), VisibleAnywhere)
		TArray<class AItemActor*> ShopItemList;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "npcType == ENPCType::TALK", EditConditionHides))
		TArray<FString> talk;

};
