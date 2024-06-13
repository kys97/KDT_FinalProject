// Fill out your copyright notice in the Description page of Project Settings.


#include "NetSession.h"

CNetSession::CNetSession()
{
}

CNetSession::~CNetSession()
{
	Close();
}

bool CNetSession::Connect(const FString& IPAddr, int32 Port)
{
	// 소켓 생성
	mSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(
		NAME_Stream, TEXT("Default"), false);	// (소켓 타입, 설명, false = TCP / true = UDP)

	// IP주소와 포트번호 생성
	FIPv4Address IPObject;
	FIPv4Address::Parse(IPAddr, IPObject);	// 문자열로 들어온 주소를 정수로 변경해준다.

	TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	Addr->SetIp(IPObject.Value);
	Addr->SetPort(Port);

	mConnect = mSocket->Connect(*Addr);

	return mConnect;
}

void CNetSession::Close()
{
	if (mConnect)
	{
		mSocket->Close();
		delete mSocket;	// 소켓은 무조건 delete로 직접 제거해야 한다.

		mSocket = nullptr;
		mConnect = false;
	}
}
