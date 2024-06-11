// Fill out your copyright notice in the Description page of Project Settings.


#include "AIDragonTheSoulEater_GN.h"

AAIDragonTheSoulEater_GN::AAIDragonTheSoulEater_GN()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(
		TEXT("/Script/Engine.Material'/Game/Asset/FourEvilDragonsPBR/Materials/DragonTheSoulEater/HP_GreenMat.HP_GreenMat'"));

	if (MaterialAsset.Succeeded())
	{
		UMaterialInterface* Material = MaterialAsset.Object;
		mMesh->SetMaterial(0, Material);
	}

	mTableRowName = TEXT("Dragon_SoulEater_GN");
}

void AAIDragonTheSoulEater_GN::BeginPlay()
{
	Super::BeginPlay();
}

void AAIDragonTheSoulEater_GN::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAIDragonTheSoulEater_GN::NormalAttack()
{
	Super::NormalAttack();
}
