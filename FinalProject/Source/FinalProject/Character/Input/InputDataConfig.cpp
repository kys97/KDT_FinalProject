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
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_Item1.IA_Item1'") };
		if (Asset.Succeeded())
		{
			FirstItem = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_Item2.IA_Item2'") };
		if (Asset.Succeeded())
		{
			SecondItem = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_Item3.IA_Item3'") };
		if (Asset.Succeeded())
		{
			ThirdItem = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprint/Character/Input/IA_Item4.IA_Item4'") };
		if (Asset.Succeeded())
		{
			FourthItem = Asset.Object;
		}
	}
}
