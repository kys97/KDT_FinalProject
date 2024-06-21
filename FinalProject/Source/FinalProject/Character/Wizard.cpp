// Fill out your copyright notice in the Description page of Project Settings.


#include "Wizard.h"
#include "WizardPlayerController.h"
#include "../UI/GameWidget.h"


// Sets default values
AWizard::AWizard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Capsule Component Set
	GetCapsuleComponent()->InitCapsuleSize(40.f, 100.f);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -97));

	// Character Mesh Set
	// TODO : z 축 -90도 회전

	// Camera Arm Set
	mCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	mCameraArm->SetupAttachment(GetCapsuleComponent());
	mCameraArm->bDoCollisionTest = false; // 캐릭터 가려져도 카메라 이동 안하도록
	mCameraArm->bInheritPitch = false; // 컨트롤러 회전 안먹도록
	mCameraArm->bInheritYaw = false;
	mCameraArm->bInheritRoll = false;
	// TODO : Camera Arm Length Set

	// Camera Set
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mCamera->SetupAttachment(mCameraArm);
	// Camera 위치조정

	// Movement Set
	GetCharacterMovement()->bUseControllerDesiredRotation = true; // 컨트롤러 회전 사용
	GetCharacterMovement()->bOrientRotationToMovement = false; // 딱딱 끊겨서 회전돼서 해제

	// Controller Rotation Set
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

AWizardPlayerState* AWizard::GetWizardPlayerState()
{
	return GetPlayerState<AWizardPlayerState>();
}

// Called when the game starts or when spawned
void AWizard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Heal Skill 
	if (Invincibility)
	{
		AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();
		float healingPoint = State->mHPMax * 0.8 * DeltaTime;
		if (State->mHP < State->mHPMax)
		{
			if (State->mHP > State->mHPMax)
				State->mHP = State->mHPMax;
			else
			{
				FDamageEvent DmgEvent;
				ServerTakeDamge(healingPoint * (-1), DmgEvent, GetController(), this);
			}
		}
	}

	// Skill Cool Time
	if (mFirstSkillRemindTime > 0)
	{
		AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();

		m_fist_temp += DeltaTime;
		if (m_fist_temp >= 1)
		{
			mFirstSkillRemindTime--;
			GetController<AWizardPlayerController>()->GetGameWidget()->SetFirstSkillCoolTime(mFirstSkillRemindTime, State->mFirstSkillCoolTime);
			m_fist_temp = 0.f;

			if (mFirstSkillRemindTime == 0)
				GetController<AWizardPlayerController>()->GetGameWidget()->EndFirstSkillCoolTime();
		}
	}

	if (mSecondSkillRemindTime > 0)
	{
		AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();

		m_second_temp += DeltaTime;
		if (m_second_temp >= 1)
		{
			mSecondSkillRemindTime--;
			GetController<AWizardPlayerController>()->GetGameWidget()->SetSecondSkillCoolTime(mSecondSkillRemindTime, State->mSecondSkillCoolTime);
			m_second_temp = 0.f;

			if (mSecondSkillRemindTime == 0)
				GetController<AWizardPlayerController>()->GetGameWidget()->EndSecondSkillCoolTime();
		}
	}

	if (mThirdSkillRemindTime > 0)
	{
		AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();

		m_third_temp += DeltaTime;
		if (m_third_temp >= 1)
		{
			mThirdSkillRemindTime--;
			GetController<AWizardPlayerController>()->GetGameWidget()->SetThirdSkillCoolTime(mThirdSkillRemindTime, State->mThirdSkillCoolTime);
			m_third_temp = 0.f;

			if(mThirdSkillRemindTime == 0)
				GetController<AWizardPlayerController>()->GetGameWidget()->EndThirdSkillCoolTime();
		}
	}
}

// Called to bind functionality to input
void AWizard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AWizard::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// If Player is Invincible, Player doesnt take damage
	if (((!Invincibility) && Damage > 0) || (Invincibility && Damage < 0))
	{
		// Authority Check
		if (HasAuthority())
		{
			Damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
		}
		else
		{
			ServerTakeDamge(Damage, DamageEvent, EventInstigator, DamageCauser);
		}

		// Hp Set
		AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();
		State->mHP -= Damage;

		// Set HP UI
		SetHPUI(State->mHP / State->mHPMax);
		
		// Death Check
		if (State->mHP <= 0)
		{
			if (HasAuthority())
				SetDeath(true);
			else
				ServerSetDeath(this, true);
			// TODO : 사망처리 추후 어떻게 할건지?
		}
	}

	return Damage;
}

void AWizard::SetHPUI(const float hp_rate)
{
	// HP UI Set
	GetController<AWizardPlayerController>()->GetGameWidget()->SetHPBar(hp_rate);
}

void AWizard::SetMPUI(const float mp_rate)
{
	// MP UI Set
	GetController<AWizardPlayerController>()->GetGameWidget()->SetMPBar(mp_rate);
}

void AWizard::UseFirstSkill(const float cooltime)
{
	mFirstSkillRemindTime = cooltime;
	GetController<AWizardPlayerController>()->GetGameWidget()->SetFirstSkillCoolTime(mFirstSkillRemindTime, cooltime);
}

void AWizard::UseSecondSkill(const float cooltime)
{
	mSecondSkillRemindTime = cooltime;
	GetController<AWizardPlayerController>()->GetGameWidget()->SetSecondSkillCoolTime(mSecondSkillRemindTime, cooltime);
}

void AWizard::UseThirdSkill(const float cooltime)
{
	mThirdSkillRemindTime = cooltime;
	GetController<AWizardPlayerController>()->GetGameWidget()->SetThirdSkillCoolTime(mThirdSkillRemindTime, cooltime);
}

void AWizard::NormalAttack() {}
void AWizard::FirstSkill() {}
void AWizard::SecondSkill() {}
void AWizard::ThirdSkill() {}
void AWizard::FourthSkill() {}



void AWizard::ServerTakeDamge_Implementation(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}
bool AWizard::ServerTakeDamge_Validate(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return true;
}

void AWizard::ServerAttack_Implementation(AActor* DamagedActor, float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (DamagedActor)
	{
		DamagedActor->TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	}
}
bool AWizard::ServerAttack_Validate(AActor* DamagedActor, float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return true;
}



void AWizard::ChangeAttackAnimInstance_Implementation(EWizardAttackAnimTypes animType)
{
	mAnimInstance->PlayAnimation(animType);
}
void AWizard::ServerChangeAttackAnimInstance_Implementation(AWizard* MoveActor, EWizardAttackAnimTypes animType)
{
	if(MoveActor)
	{
		MoveActor->mAnimInstance->PlayAnimation(animType);
	}
}



void AWizard::SetMove_Implementation(bool move)
{
	mAnimInstance->SetMove(move);
}

void AWizard::ServerSetMove_Implementation(AWizard* MoveActor, bool move)
{
	MoveActor->SetMove(move);
}



void AWizard::SetDeath_Implementation(bool death)
{
	mAnimInstance->SetDeath(death);
}

void AWizard::ServerSetDeath_Implementation(AWizard* DeathActor, bool death)
{
	DeathActor->mAnimInstance->SetDeath(death);
}