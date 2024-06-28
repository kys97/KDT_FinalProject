// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "ItemActor.h"
#include "MPPotionItem.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AMPPotionItem : public AItemActor
{
	GENERATED_BODY()

public:
	AMPPotionItem();

public:
	UFUNCTION()
	void OnItemCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
