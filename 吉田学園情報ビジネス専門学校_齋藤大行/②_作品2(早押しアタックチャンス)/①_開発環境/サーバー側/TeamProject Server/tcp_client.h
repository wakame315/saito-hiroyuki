//=============================================================================
//
// TCPクライアント定義 [TCP_client.h]
// Author :齋藤大行
//
//=============================================================================
#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_
#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
//インクルードファイル
//=============================================================================
#include<WinSock2.h>
#include<stdio.h>

//=============================================================================
//マクロ定義
//=============================================================================
#define SERVER_PORT_NUM 12345
#define MAX_ACCEPT_CONNECTION 5
#define BUFFER_NUM 1024

//=============================================================================
//クラス定義
//=============================================================================
class CTcpClient
{
public:
	CTcpClient();														 //コンストラクタ
	~CTcpClient();														 //デストラクタ
	static CTcpClient *Create(const char*pHostName, int nPortNum);		 //生成処理
	static CTcpClient *Create(SOCKET sock);								 //生成処理(アクセプトによる接続)
	void Release(void);													 //終了判定処理
	bool Init(const char *pHostName, int nPortNum);						 //初期化処理
	bool Init(SOCKET sock);												 //初期化処理(アクセプトによる接続)
	int Send(char * pSendData, int nSendDataSize);						 //送信処理
	int Recv(char *pRecvBuf, int nRecvBuffSize);						 //受信処理

	void Close();														 //終了処理

private:
	SOCKET m_sock;
};


#endif 
