// Fill out your copyright notice in the Description page of Project Settings.


#include "Wizard.h"

// Sets default values
AWizard::AWizard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Capsule Component Set
	GetCapsuleComponent()->InitCapsuleSize(40.f, 100.f);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -97));

	// Character Mesh Set
	// TODO : z 축 -90도 회전

	// Camera Arm Set
	mCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	mCameraArm->SetupAttachment(GetCapsuleComponent());
	mCameraArm->bDoCollisionTest = false; // 캐릭터 가려져도 카메라 이동 안하도록
	// TODO : Camera Arm Length Set

	// Camera Set
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mCamera->SetupAttachment(mCameraArm);
	// Camera 위치조정
}

// Called when the game starts or when spawned
void AWizard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWizard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AWizard::NormalAttack()
{
}
