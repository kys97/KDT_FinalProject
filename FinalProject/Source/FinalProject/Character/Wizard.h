// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

#include "WizardAnimInstance.h"
#include "WizardPlayerState.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Invincibility = false;

private:
	int32 mFirstSkillRemindTime;
	float m_fist_temp;
	int32 mSecondSkillRemindTime;
	float m_second_temp;
	int32 mThirdSkillRemindTime;
	float m_third_temp;

public:
	bool GetMoveEnabled() { return mAnimInstance->MoveEnable(); }
	bool GetWizardDeath() { return mAnimInstance->GetIsDeath(); }
	AWizardPlayerState* GetWizardPlayerState();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	void HealHP(bool IsHealing) { Invincibility = IsHealing; }

protected:
	void SetHPUI(const float hp_rate);
	void SetMPUI(const float mp_rate);

	void UseFirstSkill(const float cooltime);
	void UseSecondSkill(const float cooltime);
	void UseThirdSkill(const float cooltime);

public:
	virtual void NormalAttack();
	virtual void FirstSkill();
	virtual void SecondSkill();
	virtual void ThirdSkill();
	virtual void FourthSkill();

public:
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerTakeDamge(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerAttack(AActor* DamagedActor, float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);


	UFUNCTION(NetMulticast, Reliable)
	void ChangeAttackAnimInstance(EWizardAttackAnimTypes animType);
	UFUNCTION(Server, Reliable)
	void ServerChangeAttackAnimInstance(AWizard* MoveActor, EWizardAttackAnimTypes animType);


	UFUNCTION(NetMulticast, Reliable)
	void SetMove(bool move);
	UFUNCTION(Server, Reliable)
	void ServerSetMove(AWizard* MoveActor, bool move);

	UFUNCTION(NetMulticast, Reliable)
	void SetDeath(bool death);
	UFUNCTION(Server, Reliable)
	void ServerSetDeath(AWizard* DeathActor, bool death);
};
