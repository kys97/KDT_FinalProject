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

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

private:
	void BeginDelayOver();
	void SkillDelayOver();
	void DestoyStorm();

private:
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerAttack(AActor* DamagedActor, float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

};
