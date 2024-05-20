// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardPlayerController.h"


AWizardPlayerController::AWizardPlayerController()
{

}

void AWizardPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// UI Input Mode Setting
	FInputModeGameAndUI input;
	SetInputMode(input);
	bShowMouseCursor = true;

	// Mapping Input Context
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	const UInputDataConfig* InputDataConfig = GetDefault<UInputDataConfig>();
	Subsystem->AddMappingContext(InputDataConfig->WizardInputContext, 0);
}

void AWizardPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind Action
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);
	const UInputDataConfig* MainInputDataConfig = GetDefault<UInputDataConfig>();
	EnhancedInputComponent->BindAction(MainInputDataConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::OnMove);

}

void AWizardPlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	APawn* mPawn = GetPawn();

	// Get Rotate & Move Vector
	const FRotator Rotation = K2_GetActorRotation();
	const FRotator YawRotation = FRotator(0.0, Rotation.Yaw, 0.0);
	const FVector FwdVector = YawRotation.Vector();
	const FVector RightVector = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);

	// Set Move
	// Action.X > 0 ? Right : Left
	// Action.Y > 0 ? Fwd : Bwd 
	const FVector ActionValue = InputActionValue.Get<FVector>();
	// 앞 뒤
	mPawn->AddMovementInput(FwdVector, ActionValue.Y);
	// 좌우
	mPawn->AddMovementInput(RightVector, ActionValue.X);
	
}
