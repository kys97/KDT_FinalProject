// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageText.h"
#include "../UI/AIHUDWidget.h"

// Sets default values
ADamageText::ADamageText()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRootComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	SetRootComponent(mRootComp);

	mDamageTextComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPWidget"));
	mDamageTextComp->SetupAttachment(mRootComp);

	static ConstructorHelpers::FClassFinder<UUserWidget>
		DamageTextClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/Monster/UI_TakeDamage.UI_TakeDamage_C'"));
	if (DamageTextClass.Succeeded())
	{
		mDamageTextClass = DamageTextClass.Class;
		mDamageTextComp->SetWidgetClass(mDamageTextClass);
	}

	mDamageTextComp->SetWidgetSpace(EWidgetSpace::World);
	mDamageTextComp->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	mDamageTextComp->SetDrawSize(FVector2D(300.f, 200.f));
	mDamageTextComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ADamageText::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADamageText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(mDamageText))
	{
		DestroyTime += DeltaTime;

		if (DestroyTime > 3.f)
			Destroy();
	}
}

void ADamageText::SetDamage(float Damage)
{
	mDamage = Damage;

	mDamageText = Cast<UAIHUDWidget>(mDamageTextComp->GetWidget());
	if (IsValid(mDamageText))
	{
		mDamageText->AddConstructDelegate<ADamageText>(this, &ADamageText::SetWidgetDamageText);
	}
}

void ADamageText::SetWidgetDamageText()
{
	mDamageText->SetWidgetDamageText(mDamage);
}

