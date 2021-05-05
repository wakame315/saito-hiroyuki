//********************************************
//インクルードファイル
//********************************************
#include "protocol_ranking.h"
#include "tcp_client.h"
#include "main.h"

void GetRanking(RankingData * pRankingData)
{
	WSADATA wsaData;
	char aRecvBuf[128];
	char aSendBuf[128];

	//winsock初期化
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);
	if (nErr != 0)
	{
		//何らかの原因で失敗した
		printf("WSAStartup failed\n");
	}

	CTcpClient * pTcpClient = NULL;

	if (pTcpClient == NULL)
	{
		pTcpClient = CTcpClient::Create(IPADDRESS, SERVER_PORT_NUM);

		if (pTcpClient == NULL)
		{
			//winsock終了処理
			WSACleanup();
		}
	}
	aSendBuf[0] = COMMAND_TYPE_GET_RANKING;

	pTcpClient->Send(aSendBuf, strlen(aSendBuf));

	memset(aSendBuf, 0, sizeof(aSendBuf));

	pTcpClient->Recv(aRecvBuf, sizeof(aRecvBuf));

	int nIndex = 0;
	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		int nTime = *(int*)&aRecvBuf[nIndex];
		nTime = ntohl(nTime);
		pRankingData[nCntRank].nClearTime = nTime;
		nIndex += sizeof(int);
		memcpy(pRankingData[nCntRank].aName, &aRecvBuf[nIndex], MAX_NAME);
		nIndex += MAX_NAME;
	}

	pTcpClient->Release();

	//winsock終了処理
	WSACleanup();
}



int SetRanking(int nTime)
{
	WSADATA wsaData;

	//winsock初期化
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);
	if (nErr != 0)
	{
		//何らかの原因で失敗した
		printf("WSAStartup failed\n");
	}

	//tcp送受信クラスの作成
	CTcpClient * pTcpClient = CTcpClient::Create(IPADDRESS, SERVER_PORT_NUM);
	if (pTcpClient == NULL)
	{
		return 0;
	}

	//ランキング設定リクエストの送信

	//一バイト目：COMMAND_TYPE_SET_RANKING
	char aSenBuf[128];
	aSenBuf[0] = COMMAND_TYPE_SET_RANKING;

	//2～5バイト目：クリアタイムを設定（エンディアン変換はhtonl関数を使用）
	nTime = htonl(nTime);
	memcpy(&aSenBuf[1], &nTime, sizeof(int));
	//6～13バイト目：名前を設定
	memcpy(&aSenBuf[5], &"名前", MAX_NAME);
	//送信
	pTcpClient->Send(aSenBuf, 13);

	//ランキング設定のレスポンスを受信
	char aRecvBuf[128];
	memset(aRecvBuf, 0, sizeof(aRecvBuf));
	pTcpClient->Recv(aRecvBuf, sizeof(aRecvBuf));

	//切断処理
	pTcpClient->Release();

	//winsock終了処理
	WSACleanup();

	return aRecvBuf[0];
}
