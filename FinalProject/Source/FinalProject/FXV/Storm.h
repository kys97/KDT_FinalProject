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

	float mScale; // 0.2 ~ 1.0
	float mFadeSpeed;
	float mMoveSpeed;

public:
	FVector mMoveDir;

private:
	bool IsMove;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void BeginDelayOver();

public:	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnOutSideCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnInSideCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void SkillDelayOver();
	void DestoyStorm();


};
