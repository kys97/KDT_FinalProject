// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicStaff.h"

#include "../Character/WizardPlayerState.h"


// Sets default values
AMagicStaff::AMagicStaff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(mRoot);

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mMesh->SetupAttachment(mRoot);
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMagicStaff::SetInputActionBind(AWizard* Character)
{
	if (Character == nullptr)
		return;

	// Input Setting
	if (AWizardPlayerController* WizardPlayerController = Cast<AWizardPlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(WizardPlayerController->GetLocalPlayer()))
		{
			const UInputDataConfig* InputDataConfig = GetDefault< UInputDataConfig>();
			Subsystem->AddMappingContext(InputDataConfig->WizardInputContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(WizardPlayerController->InputComponent))
		{
			const UInputDataConfig* InputDataConfig = GetDefault<UInputDataConfig>();
			EnhancedInputComponent->BindAction(InputDataConfig->NormalAttack, ETriggerEvent::Triggered, this, &ThisClass::NormalAttack, Character);
			EnhancedInputComponent->BindAction(InputDataConfig->FirstSkill, ETriggerEvent::Triggered, this, &ThisClass::FirstSkill, Character);
			EnhancedInputComponent->BindAction(InputDataConfig->SecondSkill, ETriggerEvent::Triggered, this, &ThisClass::SecondSkill, Character);
			EnhancedInputComponent->BindAction(InputDataConfig->ThirdSkill, ETriggerEvent::Triggered, this, &ThisClass::ThirdSkill, Character);
			EnhancedInputComponent->BindAction(InputDataConfig->FourthSkill, ETriggerEvent::Triggered, this, &ThisClass::FourthSkill, Character);
		}
	}
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

void AMagicStaff::NormalAttack(AWizard* Character)
{
	// Character NormalAttack
	Character->NormalAttack();
}

void AMagicStaff::FirstSkill(AWizard* Character)
{
	// Character First Skill
	Character->FirstSkill();
}

void AMagicStaff::SecondSkill(AWizard* Character)
{
	// Character First Skill
	Character->SecondSkill();
}

void AMagicStaff::ThirdSkill(AWizard* Character)
{
	// Character First Skill
	Character->ThirdSkill();
}

void AMagicStaff::FourthSkill(AWizard* Character)
{
	// Character First Skill
	Character->FourthSkill();

	// Respawn Effect
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Cyan, FString::Printf(TEXT("pressed key 4")));

}

