// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "AISpawnPoint.generated.h"

UCLASS()
class FINALPROJECT_API AAISpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAISpawnPoint();

protected:
	USceneComponent* mRoot;

#if WITH_EDITORONLY_DATA
	UArrowComponent* mArror;
#endif

	// 이 포인트에서 생성할 클래스 타입을 가지고 있게 한다.
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAIPawn> mSpawnClass;

	// mSpawnClass를 이용해서 실제로 생성된 객체의 메모리 주소를 저장
	class AAIPawn* mSpawnAI;

	// 실제 생성된 객체가 제거되고
	// 지정된 시간 이후에 다시 생성하게 하기 위한 변수
	UPROPERTY(EditAnywhere)
	float mSpawnTime = 3.f;

	// 생성을 위한 시간을 계산하기 위한 누적시간 변수
	float mAccTime;

	// 순찰 PointActor를 저장할 배열
	UPROPERTY(EditAnywhere)
	TArray<class APatrolPointActor*> mPointActorArray;

	UPROPERTY(EditAnywhere)
	float DeleteTime = 10.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Spawn();

public:
	// 스폰된 AI를 nullptr로 지정하기 위한 함수
	void ClearSpawnObject();

};
