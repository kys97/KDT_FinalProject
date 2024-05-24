// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Character/BlueWizard.h"
#include "Character/WizardPlayerController.h"
#include "Character/WizardPlayerState.h"


AMainGameMode::AMainGameMode()
{
	// DefaultPawnClass = ABlueWizard::StaticClass();
	// PlayerControllerClass = AWizardPlayerController::StaticClass();
	PlayerStateClass = AWizardPlayerState::StaticClass();
}
