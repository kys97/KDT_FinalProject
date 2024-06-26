// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "ItemActor.h"
#include "ArmorPointUpgradeItem.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AArmorPointUpgradeItem : public AItemActor
{
	GENERATED_BODY()
	
public:
	AArmorPointUpgradeItem();

protected:
	float mOriginalArmorPoint;

public:
	UFUNCTION()
	void OnItemCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void ItemFinished();
};
