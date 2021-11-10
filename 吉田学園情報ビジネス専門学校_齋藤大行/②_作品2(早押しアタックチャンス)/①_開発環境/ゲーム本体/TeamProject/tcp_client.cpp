//=============================================================================
//
// TCPクライアント処理 [tcp_client.cpp]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "tcp_client.h"

//=============================================================================
//インストラクタ
//=============================================================================
CTcpClient::CTcpClient()
{
	m_sock = -1;
}

//=============================================================================
//デストラクタ
//=============================================================================
CTcpClient::~CTcpClient()
{

}

//=============================================================================
//生成処理関数
//=============================================================================
CTcpClient * CTcpClient::Create(const char * pHostName, int nPortNum)
{
	CTcpClient *pTcpclient = new CTcpClient;

	if (pTcpclient->Init(pHostName, nPortNum) == false)
	{
		delete pTcpclient;
		pTcpclient = NULL;
	}
	return pTcpclient;
}

void CTcpClient::Release(void)
{
	Close();
	delete this;
}


//=============================================================================
//初期化処理関数
//=============================================================================
bool CTcpClient::Init(const char *pHostName, int nPortNum)
{
	//接続ソケットの生成
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sock == INVALID_SOCKET)
	{
		/*printf("socket:%d\n", WSAGetLastError());
		return 1;*/
		return false;
	}

	struct sockaddr_in addr;

	//接続先の情報の設定
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPortNum);
	addr.sin_addr.S_un.S_addr = inet_addr(pHostName);

	//サーバーに接続する
	if (connect(m_sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{
		printf("connect:%d\n", WSAGetLastError());
		//ソケット接続をクローズ
		closesocket(m_sock);
		return false;
	}
	return true;
}


//=============================================================================
//送信処理関数
//=============================================================================
int CTcpClient::Send(char *pSendData, int nSendDataSize)
{
	if (m_sock <= 0)
	{
		//接続クローズ
		CTcpClient::Close();
	}

	nSendDataSize = send(m_sock, pSendData, nSendDataSize, 0);

	return nSendDataSize;
}


//=============================================================================
//受信処理関数
//=============================================================================
int CTcpClient::Recv(char *pRecvBuf, int nRecvBuffSize)
{
	if (m_sock <= 0)
	{
		//接続クローズ
		CTcpClient::Close();
	}
	nRecvBuffSize = recv(m_sock, pRecvBuf, nRecvBuffSize, 0);

	return nRecvBuffSize;
}


//=============================================================================
//終了処理関数
//=============================================================================
void CTcpClient::Close()
{
	if (m_sock <= 0)
	{
		return;
	}
	//ソケット接続をクローズ
	closesocket(m_sock);
	m_sock = -1;
}
