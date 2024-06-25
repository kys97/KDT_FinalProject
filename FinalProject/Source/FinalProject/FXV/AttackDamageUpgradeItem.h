// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "ItemActor.h"
#include "AttackDamageUpgradeItem.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AAttackDamageUpgradeItem : public AItemActor
{
	GENERATED_BODY()
	
public:
	AAttackDamageUpgradeItem();

protected:
	float mOriginalNormalAttackPoint;
	float mOriginalFirstSkillAttackPoint;
	float mOriginalSecondSkillAttackPoint;
	float mOriginalThirdSkillAttackPoint;

public:
	UFUNCTION()
	void OnItemCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void ItemFinished();

};
