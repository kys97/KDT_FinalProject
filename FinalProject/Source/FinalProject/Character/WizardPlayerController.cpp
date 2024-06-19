// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardPlayerController.h"
#include "Wizard.h"

#include "Blueprint/UserWidget.h"


AWizardPlayerController::AWizardPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> GameWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/GameUI.GameUI'"));
	if (GameWidgetClass.Succeeded())
	{
		mGameWidget = GameWidgetClass.Class;
	}
}

void AWizardPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// UI Input Mode Setting
	FInputModeGameAndUI input;
	SetInputMode(input);
	bShowMouseCursor = true;

	// Mapping Input Context
	if (IsLocalPlayerController())
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		const UInputDataConfig* InputDataConfig = GetDefault<UInputDataConfig>();
		Subsystem->AddMappingContext(InputDataConfig->WizardInputContext, 0);
	}
}

void AWizardPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind Action
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);
	const UInputDataConfig* MainInputDataConfig = GetDefault<UInputDataConfig>();
	EnhancedInputComponent->BindAction(MainInputDataConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
	EnhancedInputComponent->BindAction(MainInputDataConfig->Move, ETriggerEvent::Completed, this, &ThisClass::EndMove);
}

void AWizardPlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	if (IsLocalPlayerController())
	{
		AWizard* Wizard = Cast<AWizard>(GetPawn());

		if (Wizard->GetMoveEnabled())
		{
			// Set Move
			if (Wizard->HasAuthority())
				Wizard->SetMove(true);
			else
				Wizard->ServerSetMove(Wizard, true);

			// InputVector.X > 0 ? Right1 : Left-1
			// InputVector.Y > 0 ? Fwd1 : Bwd-1 
			FVector2D InputVector = InputActionValue.Get<FVector2D>();
			float InputSizeSquared = InputVector.SquaredLength(); // : 1 ~ 2
			if (InputSizeSquared > 1.0f) InputVector.Normalize(); // : 1
			FVector MoveDirection = FVector(InputVector.Y, InputVector.X, 0.f);
			Wizard->AddMovementInput(MoveDirection, 1.f);

			// Set Rotate
			FRotator TargetRotation = MoveDirection.Rotation();
			// 회전 보간
			FRotator NewRotation = FMath::RInterpTo(Wizard->GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 5.0f);
			SetControlRotation(NewRotation);
		}
	}
}

void AWizardPlayerController::EndMove(const FInputActionValue& InputActionValue)
{
	AWizard* Wizard = Cast<AWizard>(GetPawn());

	if (Wizard)
	{
		if (Wizard->HasAuthority())
			Wizard->SetMove(false);
		else
			Wizard->ServerSetMove(Wizard, false);
	}
}

