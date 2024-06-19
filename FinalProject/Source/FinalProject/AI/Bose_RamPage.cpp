// Fill out your copyright notice in the Description page of Project Settings.

#include "Bose_RamPage.h"
#include "BoseAIController.h"

ABose_RamPage::ABose_RamPage()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonRampage/Characters/Heroes/Rampage/Meshes/Rampage.Rampage'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/AI/Monster/Animation/AB_RamPage.AB_RamPage_C'"));

	if (AnimAsset.Succeeded())
		mMesh->SetAnimInstanceClass(AnimAsset.Class);

	AIControllerClass = ABoseAIController::StaticClass();

	mMesh->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	mMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f)); // Pitch(Y), Yaw(Z), Roll(X)
	mMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	mCapsule->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
	mCapsule->SetCapsuleHalfHeight(100.f);
	mCapsule->SetCapsuleRadius(100.f);

	mTableRowName = TEXT("Dragon_SoulEater");
}

void ABose_RamPage::BeginPlay()
{
	Super::BeginPlay();
}

void ABose_RamPage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABose_RamPage::NormalAttack()
{
}
