// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingSton.h"

AFallingSton::AFallingSton()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> StonParticle{ TEXT("/Script/Engine.ParticleSystem'/Game/AI/Asset/Particle/P_Beam_Laser_Fire_Hit.P_Beam_Laser_Fire_Hit'") };
	if (StonParticle.Succeeded())
	{
		mParticle->SetTemplate(StonParticle.Object);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> FallEndParticle{ TEXT("/Script/Engine.ParticleSystem'/Game/AI/Asset/Particle/P_ProjectileLob_Bomblet_Impact.P_ProjectileLob_Bomblet_Impact'") };
	if (FallEndParticle.Succeeded())
	{
		mStonFallEndEffect = FallEndParticle.Object;
	}


	mStonDestroyComp = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("StonDestroyComp"));
	SetRootComponent(mStonDestroyComp);

	mCapsule->SetupAttachment(mStonDestroyComp);

	// 지오메트리 컬렉션 애셋 로드
	static ConstructorHelpers::FObjectFinder<UGeometryCollection> GeometryCollectionAssetFinder(
		TEXT("/Script/GeometryCollectionEngine.GeometryCollection'/Game/AI/Asset/Particle/SM_Rock_To_Hold_SM_Rock_To_Hold/FallingSton_GeometryCollection.FallingSton_GeometryCollection'"));
	if (GeometryCollectionAssetFinder.Succeeded())
	{
		mStonDestroyAsset = GeometryCollectionAssetFinder.Object;
		mStonDestroyComp->SetRestCollection(mStonDestroyAsset.Get());
	}

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh{ TEXT("/Script/Engine.StaticMesh'/Game/AI/Asset/Particle/SM_Rock_To_Hold.SM_Rock_To_Hold'") };
	//if (!Mesh.Succeeded())
	//{
	//	check(false);
	//}
	//mMesh->SetStaticMesh(Mesh.Object);
	//
	//mMesh->SetRelativeScale3D(FVector(1.2f, 1.2f, 0.8f));

	mCapsule->SetCollisionProfileName(TEXT("BossSkill"));
	mCapsule->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	mCapsule->SetCapsuleHalfHeight(300);
	mCapsule->SetCapsuleRadius(150);

	mParticle->SetRelativeLocation(FVector(0.f, 0.f, -30.f));
	mParticle->SetRelativeScale3D(FVector(5.0f, 0.5f, 5.0f));

	TileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("TileMoveComp");
	TileMoveComp->InitialSpeed = 500.f;
	TileMoveComp->MaxSpeed = 1500.f;
	TileMoveComp->bRotationFollowsVelocity = true;
	TileMoveComp->ProjectileGravityScale = 10.f;
	TileMoveComp->SetUpdatedComponent(mMesh);
}

void AFallingSton::BeginPlay()
{
	Super::BeginPlay();

	mCapsule->OnComponentBeginOverlap.AddDynamic(this, &AFallingSton::BeginOverlap);
	mCapsule->OnComponentEndOverlap.AddDynamic(this, &AFallingSton::EndOverlap);
	mMesh->OnComponentHit.AddDynamic(this, &AFallingSton::OnComponentHit);
}

void AFallingSton::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AFallingSton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mIsOverlap)
	{
		mAttackTime += DeltaTime;
		if (mAttackTime > mAttackDuration)
		{
			FDamageEvent DmgEvent;
			OverlapActor->TakeDamage(30, DmgEvent, GetInstigatorController(), this);

			mAttackTime = 0.f;
		}
	}
}

void AFallingSton::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("AFallingSton")));

	mIsOverlap = true;
	mAttackTime = 0.f;
	OverlapActor = OtherActor;

	FDamageEvent DmgEvent;
	OverlapActor->TakeDamage(30, DmgEvent, GetInstigatorController(), this);
}

void AFallingSton::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	mIsOverlap = false;
	mAttackTime = 0.f;
	OverlapActor = nullptr;
}

void AFallingSton::OnComponentHit(UPrimitiveComponent* HitComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("AFallingSton::OnComponentHit")));

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mStonFallEndEffect,
		FVector((Hit.ImpactPoint.X), (Hit.ImpactPoint.Y), 0.f), FRotator::ZeroRotator, FVector(2.f, 2.f, 1.f));
}
