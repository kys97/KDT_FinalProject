// Fill out your copyright notice in the Description page of Project Settings.


#include "AIDragonTheSoulEater_GY.h"

AAIDragonTheSoulEater_GY::AAIDragonTheSoulEater_GY()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(
		TEXT("/Script/Engine.Material'/Game/Asset/FourEvilDragonsPBR/Materials/DragonTheSoulEater/HP_GreyMat.HP_GreyMat'"));

	if (MaterialAsset.Succeeded())
	{
		UMaterialInterface* Material = MaterialAsset.Object;
		mMesh->SetMaterial(0, Material);
	}

	mTableRowName = TEXT("Dragon_SoulEater_GY");
}

void AAIDragonTheSoulEater_GY::BeginPlay()
{
	Super::BeginPlay();
}

void AAIDragonTheSoulEater_GY::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAIDragonTheSoulEater_GY::NormalAttack()
{
	Super::NormalAttack();
}
