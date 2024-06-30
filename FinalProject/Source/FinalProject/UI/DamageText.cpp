// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageText.h"
#include "../UI/AIHUDWidget.h"

// Sets default values
ADamageText::ADamageText()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mDamageTextComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPWidget"));
	SetRootComponent(mDamageTextComp);

	static ConstructorHelpers::FClassFinder<UUserWidget>
		DamageTextClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/Monster/UI_TakeDamage.UI_TakeDamage_C'"));
	if (DamageTextClass.Succeeded())
		mDamageTextComp->SetWidgetClass(DamageTextClass.Class);

	mDamageTextComp->SetWidgetSpace(EWidgetSpace::Screen);
	mDamageTextComp->SetDrawSize(FVector2D(120.f, 40.f));
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

