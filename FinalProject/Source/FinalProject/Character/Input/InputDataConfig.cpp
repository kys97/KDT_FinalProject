// Fill out your copyright notice in the Description page of Project Settings.


#include "InputDataConfig.h"

UInputDataConfig::UInputDataConfig()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Blueprint/Character/Input/IMC_Wizard.IMC_Wizard'") };
		if (Asset.Succeeded())
		{
			WizardInputContext = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_Move.IA_Move'") };
		if (Asset.Succeeded())
		{
			Move = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_NormalAttack.IA_NormalAttack'") };
		if (Asset.Succeeded())
		{
			NormalAttack = Asset.Object;
		}
	}
}
