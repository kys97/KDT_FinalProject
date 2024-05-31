// Fill out your copyright notice in the Description page of Project Settings.

#include "AIDragonTheSoulEater.h"
#include "../Effect/EffectBase.h"
#include "MonsterState.h"

AAIDragonTheSoulEater::AAIDragonTheSoulEater()
{
	PrimaryActorTick.bCanEverTick = true; 

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/FourEvilDragonsPBR/Meshes/DrangonTheSoulEater/DragonTheSoulEaterSK.DragonTheSoulEaterSK'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/AI/Monster/Animation/AB_DragonTheSoulEater.AB_DragonTheSoulEater_C'"));

	if (AnimAsset.Succeeded())
		mMesh->SetAnimInstanceClass(AnimAsset.Class);

	mMesh->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	mMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f)); // Pitch(Y), Yaw(Z), Roll(X)
	mMesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));

	mCapsule->SetCapsuleHalfHeight(100.f);
	mCapsule->SetCapsuleRadius(100.f);

	mTableRowName = TEXT("Dragon_SoulEater");
}

void AAIDragonTheSoulEater::BeginPlay()
{
	Super::BeginPlay();
}

void AAIDragonTheSoulEater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAIDragonTheSoulEater::NormalAttack()
{
	FCollisionQueryParams param(NAME_None, false, this);

	mMonsterState = GetState<UMonsterState>();

	// 액터 위치 + 액터의 전방방향
	FVector StartLocation = GetActorLocation() + GetActorForwardVector();

	// 시작 위치 + 액터의 전방방향 * (캡슐반경+공격거리) 이므로
	// 시작위치에서 앞으로 (캡슐반경+공격거리) 만큼 이동한 위치가 끝 위치
	FVector EndLocation = StartLocation + GetActorForwardVector() * (GetCapsuleRadius() + mMonsterState->mAttackDistance);

	TArray<FHitResult> resultArray;
	// 시작위치에서 끝 위치 사이에 감지되는 결과
	bool IsCollision = GetWorld()->SweepMultiByChannel(resultArray, StartLocation, EndLocation,
		FQuat::Identity, ECC_GameTraceChannel5, FCollisionShape::MakeSphere(GetCapsuleRadius()), param);

#if ENABLE_DRAW_DEBUG

	FColor DrawColor = IsCollision ? FColor::Red : FColor::Green;

	DrawDebugCapsule(GetWorld(), (StartLocation + EndLocation) / 2.f, 
		mMonsterState->mAttackDistance, GetCapsuleRadius(),
		FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 1.f);

#endif

	if (IsCollision)
	{
		//for (auto Hit : resultArray)
		for(int32 i = 0; i < resultArray.Num(); ++i)
		{
			FDamageEvent DmgEvent;

			// TakeDamage() : 데미지 정도, 데미지 이벤트, 가해자 컨트롤러, 가해자 액터
			resultArray[i].GetActor()->TakeDamage(mMonsterState->mAttackPower, DmgEvent, GetController(), this);

			// 이펙트 출력 및 사운드 재생
			FActorSpawnParameters SpawnParam;

			SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AEffectBase* Effect = GetWorld()->SpawnActor<AEffectBase>(
				resultArray[i].ImpactPoint,
				resultArray[i].ImpactNormal.Rotation(), 
				SpawnParam);

			Effect->SetParticleAsset(TEXT(""));
			Effect->SetSoundAsset(TEXT("/Script/Engine.SoundWave'/Game/AI/Monster/Sound/Rampage_Effort_Ability_Primary_01.Rampage_Effort_Ability_Primary_01'"));
		}
	}
}
