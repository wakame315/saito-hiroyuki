#include "tcp_client.h"

CTcpClient::CTcpClient()
{
	m_sock = -1;
}

CTcpClient::~CTcpClient()
{
}

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

//=============================================================================
// CTcpClient生成 (acceptによる接続)
//=============================================================================

CTcpClient* CTcpClient::Create(SOCKET sock)
{
	CTcpClient *pTcpclient = new CTcpClient;

	if (pTcpclient->Init(sock) == false)
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

//初期化関数
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

// 初期化処理
bool CTcpClient::Init(SOCKET sock)
{
	m_sock = sock;

	return true;
}

//送信関数
int CTcpClient::Send(char *pSendData, int nSendDataSize)
{
	if (m_sock <= 0)
	{
		//接続クローズ
		return 0;
	}

	nSendDataSize = send(m_sock, pSendData, nSendDataSize, 0);

	return nSendDataSize;
}

//受信関数
int CTcpClient::Recv(char *pRecvBuf, int nRecvBuffSize)
{
	if (m_sock <= 0)
	{
		CTcpClient::Close();
	}
	nRecvBuffSize = recv(m_sock, pRecvBuf, nRecvBuffSize, 0);

	return nRecvBuffSize;
}

//終了関数
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
