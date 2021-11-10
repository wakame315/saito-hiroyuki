//=============================================================================
//
// TCPクライアント定義 [tcp_client.h]
// Author : 齋藤大行
//
//=============================================================================
#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"



//=============================================================================
// クラス宣言
//=============================================================================
class CTcpClient
{
public:
	CTcpClient();														//コンストラクタ
	~CTcpClient();														//デストラクタ
	static CTcpClient *Create(const char*pHostName, int nPortNum);		//生成処理
	void Release(void);													//終了判定処理
	bool Init(const char *pHostName, int nPortNum);						//初期化処理
	int Send(char * pSendData, int nSendDataSize);						//送信処理
	int Recv(char *pRecvBuf, int nRecvBuffSize);						//受信処理
																		
	void Close();														//終了処理

private:
	SOCKET m_sock;

};


#endif 
