// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Character/Wizard.h"
#include "Character/WizardPlayerController.h"

AMainGameMode::AMainGameMode()
{
	DefaultPawnClass = AWizard::StaticClass();
	PlayerControllerClass = AWizardPlayerController::StaticClass();
}
