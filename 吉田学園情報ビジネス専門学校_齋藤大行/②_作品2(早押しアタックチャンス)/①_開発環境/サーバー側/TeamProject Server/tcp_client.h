#pragma once
#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_
#define _CRT_SECURE_NO_WARNINGS

//==============================================
//インクルードファイル
//==============================================
#include<WinSock2.h>
#include<stdio.h>

//==============================================
//マクロ定義
//=============================================
#define SERVER_PORT_NUM 12345
#define MAX_ACCEPT_CONNECTION 5
#define BUFFER_NUM 1024

class CTcpClient
{
public:
	CTcpClient();
	~CTcpClient();
	static CTcpClient *Create(const char*pHostName, int nPortNum);
	static CTcpClient *Create(SOCKET sock);
	void Release(void);
	bool Init(const char *pHostName, int nPortNum);
	bool Init(SOCKET sock);
	int Send(char * pSendData, int nSendDataSize);
	int Recv(char *pRecvBuf, int nRecvBuffSize);

	void Close();

private:
	SOCKET m_sock;
};


#endif 
