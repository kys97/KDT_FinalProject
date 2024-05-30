// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "EffectBase.generated.h"

UCLASS()
class FINALPROJECT_API AEffectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffectBase();

protected:
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* mParticle;

	UPROPERTY(EditAnywhere)
	UAudioComponent* mAudio;
	//USoundBase* mSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetParticleAsset(const FString& Path);
	void SetParticleAsset(UParticleSystem* Particle);
	void SetSoundAsset(const FString& Path);
	void SetSoundAsset(USoundBase* Sound);

	UFUNCTION()
	void OnParticleFinish(UParticleSystemComponent* Particle);
};
