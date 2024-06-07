// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

#include "WizardAnimInstance.h"

#include "GameFramework/Character.h"
#include "Wizard.generated.h"


UCLASS()
class FINALPROJECT_API AWizard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWizard();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* mCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* mCameraArm;

	UPROPERTY(VisibleAnywhere)
	class AMagicStaff* mWeapon;

	class UWizardAnimInstance* mAnimInstance;

public:
	bool GetMoveEnabled() { return mAnimInstance->MoveEnable(); }
	void SetMove(bool move) { mAnimInstance->SetMove(move); }
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	virtual void NormalAttack();
	virtual void FirstSkill();
	virtual void SecondSkill();
	virtual void ThirdSkill();
	virtual void FourthSkill();
};
