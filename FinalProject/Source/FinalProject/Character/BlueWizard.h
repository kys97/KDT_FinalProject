// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wizard.h"
#include "BlueWizard.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API ABlueWizard : public AWizard
{
	GENERATED_BODY()

public:
	ABlueWizard();

protected:
	UStaticMesh* mWeaponMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void NormalAttack() override;

};
