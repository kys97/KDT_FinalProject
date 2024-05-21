// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardPlayerController.h"
#include "Wizard.h"


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
	APawn* WizardPawn = GetPawn();

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
	WizardPawn->AddMovementInput(FwdVector, ActionValue.Y);
	// 좌우
	WizardPawn->AddMovementInput(RightVector, ActionValue.X);
	
	// Set Rotate
	/*
	AWizard* Wizard = Cast<AWizard>(GetPawn());
	Wizard->MoveDir = ActionValue.X * 90.f; // 좌 우 설정
	if (ActionValue.Y > 0) // 전방 대각선 설정
		Wizard->MoveDir -= 45.f * ActionValue.X;
	else if (ActionValue.Y < 0) // 후방 대각선 설정
		Wizard->MoveDir += 45.f * ActionValue.X;
	else if (Wizard->MoveDir == 0.f) // 앞 뒤 설정
		Wizard->MoveDir = 90.f - (ActionValue.Y * 90.f);
	*/

	if (ActionValue.SizeSquared() > 0.0f) // 입력이 존재하는 경우에만 회전
	{
		FRotator TargetRotation = ActionValue.Rotation();
		TargetRotation.Pitch = 0.0f; // 지면에 평행하게 회전
		TargetRotation.Roll = 0.0f;
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Cyan, FString::Printf(TEXT("%f"),TargetRotation.Yaw));

		AWizard* Wizard = Cast<AWizard>(WizardPawn);

		// TODO : Rotator Yaw 계산하기
		Wizard->GetMesh()->AddLocalRotation(TargetRotation);
	}
}
