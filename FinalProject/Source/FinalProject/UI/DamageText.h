// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "DamageText.generated.h"

UCLASS()
class FINALPROJECT_API ADamageText : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageText();

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mRootComp;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* mDamageTextComp;

	TSubclassOf<UUserWidget> mDamageTextClass;

	UPROPERTY(EditAnywhere)
	class UAIHUDWidget* mDamageText;

	float mDamage;

	float DestroyTime = 0.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetDamage(float Damage);
	void SetWidgetDamageText();

};