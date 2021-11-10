//=============================================================================
//
// TCPサーバー処理 [tcp_server.cpp]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "tcp_server.h"
#include "tcp_client.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CTcpListener::CTcpListener()
{
	m_sockServer = -1;
}

//=============================================================================
//デストラクタ
//=============================================================================
CTcpListener::~CTcpListener()
{

}


//=============================================================================
//終了判定処理
//=============================================================================
void CTcpListener::Release(void)
{
	Close();
	delete this;
}


//=============================================================================
//生成処理
//=============================================================================
CTcpListener* CTcpListener::Create(int nPortNum)
{
	// TCP接続受付クラスのインスタンス生成

	CTcpListener *pTcpcserver = new CTcpListener;

	if (pTcpcserver->Init(nPortNum,MAX_ACCEPT_CONNECTION) == false)
	{
		delete pTcpcserver;
		pTcpcserver = NULL;
	}

	return pTcpcserver;
}

//=============================================================================
//接続受付処理
//=============================================================================
CTcpClient* CTcpListener::Accept()
{
	struct sockaddr_in client;
	int nAddrLenght = sizeof(client);

	if (m_sockServer < 0) 
	{
		return NULL;
	}

	// 接続受付処理
	SOCKET sock = accept(m_sockServer, (struct sockaddr*)&client, &nAddrLenght);

	CTcpClient *pTcpclient = CTcpClient::Create(sock);

	return pTcpclient;
}

//=============================================================================
//初期化処理
//=============================================================================
bool CTcpListener::Init(int nPortNum, int nAcceptConnNum)
{
	struct sockaddr_in addr;
	struct sockaddr_in client;

	//接続用ソケットの作成
	m_sockServer = socket(AF_INET, SOCK_STREAM, 0);

	//接続受付情報の設定

	addr.sin_family = AF_INET;					//IPv4
	addr.sin_port = htons(SERVER_PORT_NUM);     //ポート番号
	addr.sin_addr.S_un.S_addr = INADDR_ANY;     //すべての接続を受け付ける

												//ソッケトにIPアドレスとポート番号を設定する
	bind(m_sockServer, (struct sockaddr*)&addr, sizeof(addr));

	//接続要求受付を開始する
	listen(m_sockServer, MAX_ACCEPT_CONNECTION);

	//ソケット接続を受け付ける（受け付けるまでプログラムはブロックされる）
	int nAddrLenght = sizeof(client);


	printf("接続待ちです\n");

	return true;
}

//=============================================================================
//終了処理
//=============================================================================
void CTcpListener::Close()
{
	if (m_sockServer <= 0)
	{
		return;
	}
	//ソケット接続をクローズ
	closesocket(m_sockServer);
	m_sockServer = -1;
}
