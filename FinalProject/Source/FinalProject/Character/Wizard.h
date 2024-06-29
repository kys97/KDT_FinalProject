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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* mWizardInfoWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* mCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* mCameraArm;

	UPROPERTY(VisibleAnywhere)
	class AMagicStaff* mWeapon;

	class UWizardAnimInstance* mAnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Invincibility = false;

	// Skill Var
	int32 mFirstSkillRemindTime;
	int32 mSecondSkillRemindTime;
	int32 mThirdSkillRemindTime;

private:
	// MP Var
	float m_mp_time_cnt = 0.f;

	// Skill Var
	float m_fist_temp;
	float m_second_temp;
	float m_third_temp;

	// Item Var
	int32 mHPPotionCount = 0;
	int32 mMPPotionCount = 0;
	int32 mAttackItemCount = 0;
	int32 mArmorItemCount = 0;

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
	
	void GetExp(float exp);
private:
	void CheckLevelUp();
	void SetInfoUI();
public:
	void SetExpUI(float rate);

	void HealHP(bool IsHealing);
	void SetHPUI(const float hp_rate);
	void SetMPUI(const float mp_rate);

	void GetHpItem();
	void GetMpItem();
	void GetAttackItem();
	void GetArmorItem();

	void UseHpItem();
	void UseMpItem();
	void UseAttackItem();
	void UseArmorItem();
	UFUNCTION()
	void EndAttackItem(float normal, float first, float second, float third);
	UFUNCTION()
	void EndArmorItem(float armor);

protected:
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
