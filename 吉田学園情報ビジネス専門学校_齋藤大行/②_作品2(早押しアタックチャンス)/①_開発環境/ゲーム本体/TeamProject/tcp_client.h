#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

//==============================================
//インクルードファイル
//==============================================
#include "main.h"
//==============================================
//マクロ定義
//=============================================


class CTcpClient
{
public:
	CTcpClient();
	~CTcpClient();
	static CTcpClient *Create(const char*pHostName, int nPortNum);
	void Release(void);
	bool Init(const char *pHostName, int nPortNum);
	int Send(char * pSendData, int nSendDataSize);
	int Recv(char *pRecvBuf, int nRecvBuffSize);

	void Close();

private:
	SOCKET m_sock;

};


#endif 
