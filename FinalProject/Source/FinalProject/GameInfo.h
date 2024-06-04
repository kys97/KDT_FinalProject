// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"		// "CoreMinimal.h"
#include "Engine.h"
#include "Engine/DamageEvents.h"

#include "DrawDebugHelpers.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"

// Server
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Net/UnrealNetwork.h"

#include "UObject/NoExportTypes.h"
#include "GameInfo.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EWizardAttackAnimTypes : uint8
{ 
	NormalAttack,
	FirstSkill,
	SecondSkill,
	ThirdSkill,
	FourthSkill
};

UCLASS()
class FINALPROJECT_API UGameInfo : public UObject
{
	GENERATED_BODY()
	
};
