// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"		// "CoreMinimal.h"
#include "Engine.h"
#include "Engine/DamageEvents.h"

#include "DrawDebugHelpers.h"

#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Net/UnrealNetwork.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "Components/WidgetComponent.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"

#include "NiagaraFunctionLibrary.h"

// Server
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Net/UnrealNetwork.h"

#include "UObject/NoExportTypes.h"
#include "GameInfo.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Network, Log, All);

// 플레이어 공격 Animation ENUM
UENUM(BlueprintType)
enum class EWizardAttackAnimTypes : uint8
{ 
	NormalAttack,
	FirstSkill,
	SecondSkill,
	ThirdSkill,
	FourthSkill
};

// 플레이어 직업 ENUM
UENUM(BlueprintType)
enum class EWizardJob : uint8
{
	None,
	Blue,
	Green,
	Red,
	White,
	Black,
	Count
};

// TODO : AnimInstance C++로 변환작업
UENUM(BlueprintType)
enum class EWizardAnimTypes : uint8
{
	Idle, 
	Move,
	NormalAttack,
	FirstSkill,
	SecondSkill,
	ThirdSkill,
	FourthSkill, 
	Death
};

UCLASS()
class FINALPROJECT_API UGameInfo : public UObject
{
	GENERATED_BODY()
	
};
