// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

#include "../Character/Wizard.h"
#include "../Character/WizardPlayerController.h"

#include "GameFramework/Actor.h"
#include "MagicStaff.generated.h"

UCLASS()
class FINALPROJECT_API AMagicStaff : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicStaff();

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* mRoot;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mMesh;

	TSubclassOf<class AThunder> mSecondSkillParticle;


public:
	void SetMesh(UStaticMesh* Mesh) { mMesh->SetStaticMesh(Mesh); }

	void SetInputActionBind(AWizard* Character);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void NormalAttack(AWizard* Character);
	void FirstSkill(AWizard* Character);
	void SecondSkill(AWizard* Character);
	void ThirdSkill(AWizard* Character);
	void FourthSkill(AWizard* Character);
};
