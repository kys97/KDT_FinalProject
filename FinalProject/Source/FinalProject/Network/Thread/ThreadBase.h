// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"

class FINALPROJECT_API CThreadBase : public FRunnable
{
	friend class CThreadMgr;

protected:
	CThreadBase();
	~CThreadBase();

protected:
	bool mLoop = false;
	// 쓰레드 이름
	FString mName;

public:
	void SetName(const FString& Name)
	{
		mName = Name;
	}

	void SetLoop(bool Loop)
	{
		mLoop = Loop;
	}

public:
	virtual bool Init() override;	// override 키워드 : 인자 타입이 바뀌는 것을 막아준다.
	virtual uint32 Run() final;		// final 키워드: 자식클래스에서 재정의 하지 말라는 약속.
	virtual void Stop();
	virtual void Exit();

protected:
	// 실제로 돌아갈 Run 함수
	virtual uint32 ThreadRun() = 0;
};
