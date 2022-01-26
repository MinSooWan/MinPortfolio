// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"

UENUM(BlueprintType)
enum class EBuffState : uint8
{
	NORMAL,
	GIVE_ATC_UP,
	GIVE_DEF_UP,
	GIVE_DEX_UP,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINPORTFOLIO_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuffComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		TArray<EBuffState> buffStates;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TArray<EBuffState> GetBuffStates() { return buffStates; }

	UFUNCTION(BlueprintCallable)
		void AddBuffState(EBuffState buff, const float value, const float cool);

	UFUNCTION()
		void RemoveBuffState(EBuffState buff, const float value);
};
