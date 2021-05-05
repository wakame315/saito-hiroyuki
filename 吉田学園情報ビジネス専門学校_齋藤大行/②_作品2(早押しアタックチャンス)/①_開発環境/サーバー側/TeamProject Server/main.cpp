#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
//==============================================
//インクルードファイル
//==============================================
#include <stdio.h>
#include <thread>
#include <mutex>
#include <Winsock2.h>
#include "main.h"
#include <stralign.h>

//==============================================
//マクロ定義
//=============================================
#define MAX_ACCEPT_CONNECTION 5
#define BUFFER_NUM 1024


//プロトタイプ宣言
void WorkerThread(CTcpClient *pTcpClient);
void ReadFile(void);
void WriteFile(void);
int SetRanking(int nTime, char *pName);


//グローバル変数宣言
RankingData  g_pRankingData[MAX_RANKING] = {};


//==============================================
//メイン関数
//==============================================
int main()
{
	WSADATA wsaData;
	CTcpListener *pTcpListener = NULL;

	//winsock初期化
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);
	if (nErr != 0)
	{
		//何らかの原因で失敗した
		printf("WSAStartup failed\n");
		return 1;
	}
	//グローバル変数宣言
	memset(g_pRankingData, 0, sizeof(g_pRankingData));

	//ランキングデータの読み込み
	ReadFile();

	if (pTcpListener == NULL)
	{
		pTcpListener = CTcpListener::Create(SERVER_PORT_NUM);

	}
	else
	{
		return 1;
	}
	

	while (true)
	{

		CTcpClient *pTcpClient = pTcpListener->Accept();
		if (pTcpClient == NULL)
		{
			continue;
		}

		printf("クライアントが接続しました\n");

		std::thread thworker(WorkerThread, pTcpClient);

		thworker.detach();

	}

	pTcpListener->Release();

	//winsock終了処理
	WSACleanup();

	return 0;

}
//スレッド関数
void WorkerThread(CTcpClient *pTcpClient)
{

	char aRecvBuf[BUFFER_NUM];
	char aSendBuf[BUFFER_NUM];
	char aName[MAX_NAME];
	int nRecvNum = 0;
	int nIndex = 0;
	int nTime = 0;
	int nRanking = 0;
	while (true)
	{
		

		memset(aRecvBuf, 0, sizeof(aRecvBuf));
		nRecvNum = pTcpClient->Recv(aRecvBuf, sizeof(aRecvBuf));
		if (nRecvNum <= 0)
		{
			break;
		}
		COMMAND_TYPE command = (COMMAND_TYPE)aRecvBuf[0];

		switch (command)
		{

		case COMMAND_TYPE_GET_RANKING:

			
			for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
			{
				int nData = (int)htonl(g_pRankingData[nCntRank].nClearTime);
				memcpy(&aSendBuf[nIndex], &nData, sizeof(int));
				nIndex += sizeof(int);
				g_pRankingData[nCntRank].aName[MAX_NAME - 1] = '\0';
				memcpy(&aSendBuf[nIndex], &g_pRankingData[nCntRank].aName, MAX_NAME);
				nIndex += MAX_NAME;
			}

			pTcpClient->Send(aSendBuf, nIndex);

			break;


		case COMMAND_TYPE_SET_RANKING:

			//2バイト目～5バイト目から、受信したクリアタイムを所得

			//6～13バイト目から名前を所得

			//ランキング更新

			//じゅんいを送信
			

			nTime = (int)ntohl(*(int*)&aRecvBuf[1]);
			 
			memcpy(&aName, &aRecvBuf[5], MAX_NAME);

			aName[MAX_NAME - 1] = '\0';

			nRanking = SetRanking(nTime, aName);

			aSendBuf[0] = (char)nRanking;
		
			pTcpClient->Send(aSendBuf, sizeof(char));

			break;


		default:
			break;

		}
		
	}

	printf("接続が切れました\n");

	pTcpClient->Release();
}

void ReadFile(void)
{
	FILE *pFile;
	pFile = fopen("Ranking.txt", "r");
	char aNone[10] = "NONE";
	if (pFile != NULL)
	{
		
		for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
		{
			fscanf(pFile, "%s\n", &g_pRankingData[nCnt].aName);//人数の入力
			
			fscanf(pFile, "%d\n", &g_pRankingData[nCnt].nClearTime);//人数の入力
			if (strcmp(g_pRankingData[nCnt].aName, "" ) == 0)
			{
				strcpy(g_pRankingData[nCnt].aName,aNone);
			}
			if (g_pRankingData[nCnt].nClearTime == NULL)
			{
				g_pRankingData[nCnt].nClearTime = 0;
			}
			
		}
		printf("テキストファイルを読み込みました。\n");
		fclose(pFile);
	}
	else
	{
		printf("エラーが発生した為、ファイルを読み込み出来ませんでした");
	}
}


void WriteFile(void)
{
	FILE *pFile;
	pFile = fopen("Ranking.txt", "w");
	if (pFile != NULL)
	{

		for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
		{
			fprintf(pFile, "%s\n", g_pRankingData[nCnt].aName);
			fprintf(pFile, "%d\n", g_pRankingData[nCnt].nClearTime);
		}	
		
		printf("テキストファイルにデータを出力しました\n");
		fclose(pFile);
	}
	else
	{
		printf("エラーが発生した為、ファイルが開けませんでした");

	}

}

int SetRanking(int nTime, char * pName)
{
	int nCntRank;
	int nCntMove;
	for (nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		if (nTime != NULL)
		{
			if (g_pRankingData[nCntRank].nClearTime == NULL || nTime < g_pRankingData[nCntRank].nClearTime)
			{
				if (g_pRankingData[nCntRank].nClearTime == NULL)
				{
					g_pRankingData[nCntRank].nClearTime = nTime;
					strcpy(g_pRankingData[nCntRank].aName, pName);
					break;
				}

				if (g_pRankingData[nCntRank].nClearTime > nTime)
				{
					for (nCntMove = MAX_RANKING - 1; nCntMove > nCntRank; nCntMove--)
					{
						g_pRankingData[nCntMove].nClearTime = g_pRankingData[nCntMove - 1].nClearTime;
						strcpy(g_pRankingData[nCntMove].aName, g_pRankingData[nCntMove - 1].aName);

						g_pRankingData[nCntMove].nClearTime = g_pRankingData[nCntMove].nClearTime;
						strcpy(g_pRankingData[nCntMove].aName, g_pRankingData[nCntMove].aName);

					}
					g_pRankingData[nCntRank].nClearTime = nTime;
					strcpy(g_pRankingData[nCntRank].aName, pName);
					break;

				}
			}
		}
	}

	


	WriteFile();
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		printf("名前:%s\n", g_pRankingData[nCnt].aName);
		printf("%d位%.4f秒\n", nCnt +1,(float)g_pRankingData[nCnt].nClearTime / 1000.0f);
	}

	if (nTime == NULL)
	{
		printf("結果;お手付き\n");
	}
	else
	{
		printf("結果;%d位\n", nCntRank + 1);
	}
	
	return nCntRank + 1;
}
