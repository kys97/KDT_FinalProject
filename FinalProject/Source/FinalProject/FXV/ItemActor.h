// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

#include "NiagaraComponent.h"
#include "../Character/Wizard.h"

#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

UCLASS()
class FINALPROJECT_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* mItemParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* mItemCollision;

	AWizard* ItemOwner = nullptr;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
