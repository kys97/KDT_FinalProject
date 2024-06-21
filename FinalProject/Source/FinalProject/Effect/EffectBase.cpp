// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectBase.h"

// Sets default values
AEffectBase::AEffectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	SetRootComponent(mCapsule);

	mParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	mParticle->SetupAttachment(mCapsule);
	mParticle->SetCollisionProfileName(TEXT("BossSkill"));

	mAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	mAudio->SetupAttachment(mCapsule);

#if WITH_EDITORONLY_DATA

	mParticle->bVisualizeComponent = true;

#endif // WITH_EDITORONLY_DATA
}

// Called when the game starts or when spawned
void AEffectBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEffectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEffectBase::SetParticleAsset(const FString& Path)
{
	UParticleSystem* Particle = LoadObject<UParticleSystem>(nullptr, *Path);

	SetParticleAsset(Particle);
}

void AEffectBase::SetParticleAsset(UParticleSystem* Particle)
{
	if (IsValid(Particle))
	{
		// 파티클 컴포넌트에 파티클을 지정한다.
		mParticle->SetTemplate(Particle);
		// 파티클이 끝났을 때 호출할 함수, 델리게이트에 지정
		mParticle->OnSystemFinished.AddDynamic(this, &AEffectBase::OnParticleFinish);
	}
}

void AEffectBase::SetSoundAsset(const FString& Path)
{
	USoundBase* Sound = LoadObject<USoundBase>(nullptr, *Path);

	SetSoundAsset(Sound);
}

void AEffectBase::SetSoundAsset(USoundBase* Sound)
{
	if (IsValid(Sound))
	{
		mAudio->SetSound(Sound);
		mAudio->Play();
	}
}

void AEffectBase::OnParticleFinish(UParticleSystemComponent* Particle)
{
	// 파티클이 끝났을 경우 액터를 제거한다.
	Destroy();
}

UCapsuleComponent* AEffectBase::GetCapsule()
{
	return nullptr;
}

