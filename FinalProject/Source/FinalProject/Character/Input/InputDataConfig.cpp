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
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_Skill1.IA_Skill1'") };
		if (Asset.Succeeded())
		{
			FirstSkill = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_Skill2.IA_Skill2'") };
		if (Asset.Succeeded())
		{
			SecondSkill = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_Skill3.IA_Skill3'") };
		if (Asset.Succeeded())
		{
			ThirdSkill = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_Skill4.IA_Skill4'") };
		if (Asset.Succeeded())
		{
			FourthSkill = Asset.Object;
		}
	}
}
