// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Character/BlueWizard.h"
#include "Character/WizardPlayerController.h"
#include "Character/WizardPlayerState.h"


AMainGameMode::AMainGameMode()
{
	PlayerStateClass = AWizardPlayerState::StaticClass();
}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();
}
