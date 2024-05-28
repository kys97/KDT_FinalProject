// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SkillParticleActor.h"



#include "GameFramework/Actor.h"
#include "Storm.generated.h"

UCLASS()
class FINALPROJECT_API AStorm : public ASkillParticleActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStorm();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* mInsideCollision;

	float mScale;

	float mFadeSpeed;

	float mMoveSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
