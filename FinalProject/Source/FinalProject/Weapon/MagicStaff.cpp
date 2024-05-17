// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicStaff.h"

// Sets default values
AMagicStaff::AMagicStaff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(mRoot);

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mMesh->SetupAttachment(mRoot);
}

void AMagicStaff::SetMesh(UStaticMesh* Mesh)
{
	mMesh->SetStaticMesh(Mesh);
}

// Called when the game starts or when spawned
void AMagicStaff::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMagicStaff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

