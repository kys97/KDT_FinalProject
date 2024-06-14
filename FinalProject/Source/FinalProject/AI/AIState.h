// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/ActorComponent.h"
#include "AIState.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FINALPROJECT_API UAIState : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIState();

public:
	UPROPERTY(EditAnywhere)
	FString		mName;
	// 이동 속도
	UPROPERTY(EditAnywhere)
	int32	mMoveSpeed;

	// 상호 작용을 하기 위한 거리
	UPROPERTY(EditAnywhere)
	int32	mInteractionDistance;

	FString	mDataTableRowName;

public:
	virtual void ChangeHP(float Event);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
