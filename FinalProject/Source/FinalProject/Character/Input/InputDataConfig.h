// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "InputMappingContext.h"
#include "InputAction.h"
// #include "UObject/NoExportTypes.h"
#include "InputDataConfig.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API UInputDataConfig : public UObject
{
	GENERATED_BODY()
	
public:
	UInputDataConfig();

public:
	UInputMappingContext* WizardInputContext = nullptr;

public:
	UInputAction* Move = nullptr;
	UInputAction* NormalAttack = nullptr;
};
