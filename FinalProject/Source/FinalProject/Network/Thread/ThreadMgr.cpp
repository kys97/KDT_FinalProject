// Fill out your copyright notice in the Description page of Project Settings.


#include "ThreadMgr.h"

CThreadMgr* CThreadMgr::mInst = nullptr;

CThreadMgr::CThreadMgr()
{
}

CThreadMgr::~CThreadMgr()
{
	for (auto& Thread : mThreadMap)
	{
		Thread.Value->Worker->Exit();

		// 스레드를 종료시킨다.
		Thread.Value->Thread->Kill();

		// 실제 스레드가 종료될때까지 대기한다.
		Thread.Value->Thread->WaitForCompletion();

		// 동적할당된 스레드 객체와 스레드가 동작시켜주는 클래스의 객체를
		// 제거시켜준다.
		delete Thread.Value->Thread;
		delete Thread.Value->Worker;
		delete Thread.Value;
	}
}

bool CThreadMgr::Init()
{
	return true;
}

bool CThreadMgr::SuspendThread(const FString& Name, bool Pause)
{
	if (!mThreadMap.Contains(Name))
		return false;

	mThreadMap.FindRef(Name)->Thread->Suspend(Pause);

	return true;
}

bool CThreadMgr::RemoveThread(const FString& Name)
{
	if (!mThreadMap.Contains(Name))
		return false;

	mThreadMap.FindRef(Name)->Worker->Exit();
	mThreadMap.FindRef(Name)->Thread->Kill();
	mThreadMap.FindRef(Name)->Thread->WaitForCompletion();

	delete mThreadMap.FindRef(Name)->Worker;
	delete mThreadMap.FindRef(Name)->Thread;
	delete mThreadMap.FindRef(Name);

	// Map에서 제거해준다.
	mThreadMap.Remove(Name);

	return false;
}
