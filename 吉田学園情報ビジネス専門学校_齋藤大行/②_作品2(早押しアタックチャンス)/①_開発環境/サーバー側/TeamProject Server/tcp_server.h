#pragma once
#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_
#define _CRT_SECURE_NO_WARNINGS

//==============================================
//インクルードファイル
//==============================================
#include<WinSock2.h>
#include<stdio.h>

//==============================================
//マクロ定義
//=============================================

//*********************************************************
// 前方宣言
//*********************************************************
class CTcpClient;

//*********************************************************
// TCP接続受付クラス
//*********************************************************
class CTcpListener
{
public:
	CTcpListener();
	~CTcpListener();
	static CTcpListener *Create(int nPortNum);
	CTcpClient *Accept(void);
	void Release(void);
	bool Init(int nPortNum, int nAcceptConnNum);
	void Close();

private:
	SOCKET m_sockServer;
};         


#endif 
