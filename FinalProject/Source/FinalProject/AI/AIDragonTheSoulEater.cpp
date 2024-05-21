// Fill out your copyright notice in the Description page of Project Settings.


#include "AIDragonTheSoulEater.h"

AAIDragonTheSoulEater::AAIDragonTheSoulEater()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/FourEvilDragonsPBR/Meshes/DrangonTheSoulEater/DragonTheSoulEaterSK.DragonTheSoulEaterSK'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mMesh->SetRelativeLocation(FVector(-90.f, 0.f, -27.f));
	mMesh->SetRelativeRotation(FRotator(0.f, -90.f, 90.f)); // Pitch(Y), Yaw(Z), Roll(X)
	mMesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));

	mCapsule->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	mCapsule->SetCapsuleHalfHeight(150.f);
	mCapsule->SetCapsuleRadius(90.f);

}

void AAIDragonTheSoulEater::BeginPlay()
{
	Super::BeginPlay();
}

void AAIDragonTheSoulEater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
