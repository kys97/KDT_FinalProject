// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "ThreadBase.h"

struct FThreadInfo
{
	// 실제 스레드
	FRunnableThread* Thread;
	// 스레드를 동작 시켜줄 작업자
	CThreadBase* Worker;
};

class FINALPROJECT_API CThreadMgr
{
public:
	CThreadMgr();
	~CThreadMgr();

private:
	// ThreadManager에서 이름으로 찾아서 관리할 수 있도록 해쉬맵 생성
	TMap<FString, FThreadInfo*> mThreadMap;

public:
	// 스레드를 생성할 수 있는 템플릿 함수
	template <typename T>
	FThreadInfo* CreateThread(const FString& Name)
	{
		// map에 같은 이름이 있을 경우 빠져나간다.
		// Contains() 함수 : 맵에 특정 키가 있는지 여부를 알아내기 위한 함수
		if (mThreadMap.Contains(Name))
			return nullptr;

		// ThreadInfo와 Worker를 동적할당 하고 스레드 이름 세팅
		FThreadInfo* Info = new FThreadInfo;
		Info->Worker = new T;
		Info->Worker->SetName(Name);

		Info->Worker->Init();

		// 실제 스레드를 생성하고 스레드가 동작시켜줄
		// FRunnableThread 클래스로 생성된 객체를 넘겨준다.
		Info->Thread = FRunnableThread::Create(Info->Worker, *Name);

		// 스레드를 바로 시작하는 것이 아니라 일시정지 상태로 시작되게 하고
		// 스레드를 시작해야 할 때 시작 해주도록 한다.
		Info->Thread->Suspend();

		// (키, 값) 추가
		mThreadMap.Emplace(Name, Info);

		return Info;
	}

public:
	bool Init();
	// Pause 에 true 가 들어가면 일시정지
	bool SuspendThread(const FString& Name, bool Pause);
	bool RemoveThread(const FString& Name);

private:
	static CThreadMgr* mInst;

public:
	static CThreadMgr* GetInst()
	{
		if (!mInst)
			mInst = new CThreadMgr;

		return mInst;
	}

	static void DestroyInst()
	{
		if (mInst)
		{
			delete mInst;
		}
	}
};
