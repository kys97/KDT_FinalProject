// Fill out your copyright notice in the Description page of Project Settings.


#include "AIDragonTheSoulEater.h"

AAIDragonTheSoulEater::AAIDragonTheSoulEater()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/FourEvilDragonsPBR/Meshes/DrangonTheSoulEater/DragonTheSoulEaterSK.DragonTheSoulEaterSK'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mMesh->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	mMesh->SetRelativeRotation(FRotator(0.f, 0.f, -90.f)); // Pitch(Y), Yaw(Z), Roll(X)
	mMesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));

	mCapsule->SetCapsuleHalfHeight(100.f);
	mCapsule->SetCapsuleRadius(100.f);

}

void AAIDragonTheSoulEater::BeginPlay()
{
	Super::BeginPlay();
}

void AAIDragonTheSoulEater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
