// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

#include "../Character/Wizard.h"
#include "../AI/AIMonsterPawn.h"
#include "TimerManager.h"


#include "GameFramework/Actor.h"
#include "SkillParticleActor.generated.h"

UCLASS()
class FINALPROJECT_API ASkillParticleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillParticleActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* mParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* mOutSideCollision;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWizard* SkillOwner = nullptr;

	int32 SkillDamage = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


};
