#pragma once
#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_
#define _CRT_SECURE_NO_WARNINGS

//==============================================
//�C���N���[�h�t�@�C��
//==============================================
#include<WinSock2.h>
#include<stdio.h>

//==============================================
//�}�N����`
//=============================================

//*********************************************************
// �O���錾
//*********************************************************
class CTcpClient;

//*********************************************************
// TCP�ڑ���t�N���X
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
