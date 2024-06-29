// Fill out your copyright notice in the Description page of Project Settings.


#include "Wizard.h"
#include "WizardPlayerController.h"

#include "../UI/WizardInfoWidget.h"
#include "../UI/GameWidget.h"
#include "../WizardGameInstance.h"


// Sets default values
AWizard::AWizard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Capsule Component Set
	GetCapsuleComponent()->InitCapsuleSize(40.f, 100.f);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -97));

	mWizardInfoWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InfoWidget"));
	mWizardInfoWidget->SetupAttachment(RootComponent);
	static ConstructorHelpers::FClassFinder<UWizardInfoWidget> BP_WizardInfoWidgetClass{ TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Character/BP_WizardNameWidget.BP_WizardNameWidget_C'") };
	if (BP_WizardInfoWidgetClass.Succeeded())
	{
		mWizardInfoWidget->SetWidgetClass(BP_WizardInfoWidgetClass.Class);
	}
	mWizardInfoWidget->SetWidgetSpace(EWidgetSpace::Screen);

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

	// Respawn Setting
	AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();
	if (GetGameInstance<UWizardGameInstance>()->IsRespawn())
	{
		State = GetGameInstance<UWizardGameInstance>()->GetState();
	}
	else
	{
		GetGameInstance<UWizardGameInstance>()->SetLevel(State->mLevel);
	}

	// Set Exp UI
	GetExp(0);

	// Set Item Cnt
	AWizardPlayerController* WizardController = GetController<AWizardPlayerController>();
	WizardController->GetGameWidget()->UseHPpotionItem(mHPPotionCount);
	WizardController->GetGameWidget()->UseMPpotionItem(mMPPotionCount);
	WizardController->GetGameWidget()->SetAttackItemCount(mAttackItemCount);
	WizardController->GetGameWidget()->SetArmorItemCount(mArmorItemCount);
}


void AWizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#pragma region MP Up

	m_mp_time_cnt += DeltaTime;
	if (m_mp_time_cnt > 1.f)
	{
		AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();
		State->mMP++;
		SetMPUI((float)State->mMP / (float)State->mMPMax);
		m_mp_time_cnt = 0.f;
	}

#pragma endregion

#pragma region Skill Cool Time
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
#pragma endregion

}

// Called to bind functionality to input
void AWizard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AWizard::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// If Player is Invincible, Player doesnt take damage
	if (!((Invincibility) && Damage > 0))
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

		// Damage Set
		AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();
		if (Damage > 0) // deal
		{
			Damage -= State->mArmorPoint;

			// if Damage is less than armorPoint, Take Damage Set 1
			if (Damage <= 0) Damage = 1.f;
		}

		// Take Damage
		State->mHP -= Damage;
		if (State->mHP > State->mHPMax) State->mHP = State->mHPMax;

		// Set HP UI
		SetHPUI((float)State->mHP / (float)State->mHPMax);
		
		// Death Check
		if (State->mHP <= 0)
		{
			// Collision Set
			GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
			GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

			// Data Set
			if (HasAuthority())
				SetDeath(true);
			else
				ServerSetDeath(this, true);
			
			// UI Set
			GetController<AWizardPlayerController>()->GetGameWidget()->PlayerDeath();
		}
	}

	return Damage;
}

void AWizard::GetExp(float exp)
{
	AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();
	State->mExp += exp;
	CheckLevelUp();
}

void AWizard::CheckLevelUp()
{
	AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();
	UWizardGameInstance* Instance = GetGameInstance<UWizardGameInstance>();
	while (State->mLevel * 500 < State->mExp) // level up
	{
		State->mExp -= State->mLevel * 500;
		State->mLevel++;

		Instance->SetLevel(State->mLevel);
		SetInfoUI();

		// 능력치 강화
		State->mNormalAttackPoint += 50.f;
		State->mFirstSkillAttackDamage += 50.f;
		State->mSecondSkillAttackDamage += 50.f;
		State->mThirdSkillAttackDamage += 50.f;
		State->mArmorPoint += 50.f;
		State->mHPMax += 50;
		State->mMPMax += 50;

		Instance->SetState(State);
	}
	SetExpUI(State->mExp / (State->mLevel * 500));
}

void AWizard::SetInfoUI()
{
	UWizardGameInstance* Instance = GetGameInstance<UWizardGameInstance>();
	UWizardInfoWidget* WizardInfoWidget = Cast<UWizardInfoWidget>(mWizardInfoWidget->GetWidget());
	WizardInfoWidget->SetWizardInfoText(Instance->GetLevelString().Append(Instance->GetWizardName()));
}

void AWizard::SetExpUI(float rate)
{
	GetController<AWizardPlayerController>()->GetGameWidget()->SetExpBar(rate);
}



#pragma region Set User Widget
// Set HP/MP
void AWizard::HealHP(bool IsHealing)
{
	Invincibility = IsHealing;
	AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();
	float healingPoint = State->mHPMax * 0.5;
	FDamageEvent DmgEvent;
	TakeDamage(healingPoint * (-1), DmgEvent, GetController(), this);
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

// Set Skill Cooltime
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

// Get Item
void AWizard::GetHpItem()
{
	GetController<AWizardPlayerController>()->GetGameWidget()->UseHPpotionItem(++mHPPotionCount);
}
void AWizard::GetMpItem()
{
	GetController<AWizardPlayerController>()->GetGameWidget()->UseMPpotionItem(++mMPPotionCount);
}
void AWizard::GetAttackItem()
{
	GetController<AWizardPlayerController>()->GetGameWidget()->SetAttackItemCount(++mAttackItemCount);
}
void AWizard::GetArmorItem()
{
	GetController<AWizardPlayerController>()->GetGameWidget()->SetArmorItemCount(++mArmorItemCount);
}

// Set Item
void AWizard::UseHpItem()
{
	if (mHPPotionCount > 0)
	{
		mHPPotionCount--;
		GetController<AWizardPlayerController>()->GetGameWidget()->UseHPpotionItem(mHPPotionCount);
		// How to make move Hp bar ???

		FDamageEvent DmgEvent;
		TakeDamage(-50.f, DmgEvent, GetController(), this);
	}
}
void AWizard::UseMpItem()
{
	if (mMPPotionCount > 0)
	{
		mMPPotionCount--;
		GetController<AWizardPlayerController>()->GetGameWidget()->UseMPpotionItem(mMPPotionCount);
		// How to make move Mp bar ???

		AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();
		State->mMP += 50;
		SetMPUI(State->mMP / State->mMPMax);
	}
}
void AWizard::UseAttackItem()
{
	if (mAttackItemCount > 0 && (!mIsAttackItemUsing))
	{
		mIsAttackItemUsing = true;

		// Set Data
		AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();
		float temp_normalattack = State->mNormalAttackPoint;
		float temp_firstskill = State->mFirstSkillAttackDamage;
		float temp_secondskill = State->mSecondSkillAttackDamage;
		float temp_thirdskill = State->mThirdSkillAttackDamage;
		State->mNormalAttackPoint *= 1.2f;
		State->mFirstSkillAttackDamage *= 1.2f;
		State->mSecondSkillAttackDamage *= 1.2f;
		State->mThirdSkillAttackDamage *= 1.2f;

		// UI Set
		mAttackItemCount--;
		GetController<AWizardPlayerController>()->GetGameWidget()->UseAttackPointItem(mAttackItemCount);

		// SetTimer(60s) : Parameter = origin attack point
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDel;
		TimerDel.BindUFunction(this, FName("EndAttackItem"), temp_normalattack, temp_firstskill, temp_secondskill, temp_thirdskill);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 60.0f, false);
	}
}
void AWizard::EndAttackItem(float normal, float first, float second, float third)
{
	mIsAttackItemUsing = false;

	// Set Data
	AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();
	State->mNormalAttackPoint = normal;
	State->mFirstSkillAttackDamage = first;
	State->mSecondSkillAttackDamage = second;
	State->mThirdSkillAttackDamage = third;

	// UI Set
	GetController<AWizardPlayerController>()->GetGameWidget()->EndAttackPointItem();
}
void AWizard::UseArmorItem()
{
	if (mArmorItemCount > 0 && (!mIsArmorItemUsing))
	{
		mIsArmorItemUsing = true;

		// Set Data
		AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();
		float temp_armor = State->mArmorPoint;
		State->mArmorPoint *= 1.5f;

		// UI Set
		mArmorItemCount--;
		GetController<AWizardPlayerController>()->GetGameWidget()->UseArmorPointItem(mArmorItemCount);

		// SetTimer(60s) : Parameter = origin attack point
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDel;
		TimerDel.BindUFunction(this, FName("EndArmorItem"), temp_armor);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 60.0f, false);
	}
}
void AWizard::EndArmorItem(float armor)
{
	mIsArmorItemUsing = false;

	AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();
	State->mArmorPoint = armor;

	// UI Set
	GetController<AWizardPlayerController>()->GetGameWidget()->EndArmorPointItem();
}
#pragma endregion


// Child Class override function
void AWizard::NormalAttack() {}
void AWizard::FirstSkill() {}
void AWizard::SecondSkill() {}
void AWizard::ThirdSkill() {}
void AWizard::FourthSkill() {}


#pragma region Server Function
// Take Damage
void AWizard::ServerTakeDamge_Implementation(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}
bool AWizard::ServerTakeDamge_Validate(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return true;
}

// Attack
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

// Animation
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

// Move
void AWizard::SetMove_Implementation(bool move)
{
	mAnimInstance->SetMove(move);
}
void AWizard::ServerSetMove_Implementation(AWizard* MoveActor, bool move)
{
	MoveActor->SetMove(move);
}

// Death
void AWizard::SetDeath_Implementation(bool death)
{
	mAnimInstance->SetDeath(death);
}
void AWizard::ServerSetDeath_Implementation(AWizard* DeathActor, bool death)
{
	DeathActor->mAnimInstance->SetDeath(death);
}
#pragma endregion