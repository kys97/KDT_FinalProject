// Fill out your copyright notice in the Description page of Project Settings.


#include "ThreadMgr.h"

CThreadMgr::CThreadMgr()
{
}

CThreadMgr::~CThreadMgr()
{
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
