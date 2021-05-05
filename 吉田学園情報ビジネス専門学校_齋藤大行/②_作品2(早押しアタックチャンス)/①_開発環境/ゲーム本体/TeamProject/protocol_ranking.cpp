//********************************************
//インクルードファイル
//********************************************
#include "protocol_ranking.h"
#include "tcp_client.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "displaytime.h"


LPD3DXFONT CRanking::m_pRankFont = NULL;//フォントへのポインタ
LPD3DXFONT CRanking::m_pRankingFont = NULL;//フォントへのポインタ

CRanking::CRanking()
{
	m_aName[10] = {};
}	

CRanking::~CRanking()
{
}



void CRanking::GetRanking(RankingData * pRankingData)
{
	WSADATA wsaData;
	char aRecvBuf[BUFFER_NUM];
	char aSendBuf[BUFFER_NUM];

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

	memset(aRecvBuf, 0, sizeof(aRecvBuf));

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


int CRanking::SetRanking(int nTime)
{
	CRanking * pRanking;
	pRanking = new CRanking;

	WSADATA wsaData;
	char aSenBuf[BUFFER_NUM];
	char aRecvBuf[BUFFER_NUM];//ランキング設定のレスポンスを受信
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

	pRanking->ReadFile();

	aSenBuf[0] = COMMAND_TYPE_SET_RANKING;

	//2～5バイト目：クリアタイムを設定（エンディアン変換はhtonl関数を使用）
	nTime = htonl(nTime);
	memcpy(&aSenBuf[1], &nTime, sizeof(int));
	//6～13バイト目：名前を設定
	memcpy(&aSenBuf[5], &pRanking->m_aName, MAX_NAME);
	//送信
	pTcpClient->Send(aSenBuf, 20);

	memset(aRecvBuf, 0, sizeof(aRecvBuf));

	pTcpClient->Recv(aRecvBuf, sizeof(aRecvBuf));

	//切断処理
	pTcpClient->Release();

	//winsock終了処理
	WSACleanup();

	return aRecvBuf[0];
}





void CRanking::Ranking(RankingData * RankingData, int Rank)
{
	char str[512];

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		RECT Rankingrect = { 100, 60 * (nCnt + 1), SCREEN_WIDTH, SCREEN_HEIGHT };


		sprintf(str, "順位:%d 名前:%s 結果時間:%.3f秒\n", nCnt + 1, RankingData[nCnt].aName, (float)RankingData[nCnt].nClearTime / 1000.0f);
		// テキスト描画
		m_pRankingFont->DrawText(NULL, str, -1, &Rankingrect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0, 0, 0));
	}

	RECT MyRankingrect = { 575, 250 , SCREEN_WIDTH, SCREEN_HEIGHT };

	if (CManager::GeResultTime() == NULL)
	{
		sprintf(str, "結果:お手付き");
	}
	else
	{
		if (Rank >= 11)
		{
			sprintf(str, "順位:%d\n結果時間:%.3f秒", Rank, CManager::GeResultTime() / 1000.0f);

		}
		else
		{
			sprintf(str, "順位:%d", Rank);
		}
	}


	m_pRankFont->DrawText(NULL, str, -1, &MyRankingrect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0, 0, 0));
}



void CRanking::ReadFile(void)
{
	FILE *pFile;
	pFile = fopen("NAME.txt", "r");

	if (pFile != NULL)
	{
		fscanf(pFile, "%s\n", &m_aName);

		printf("テキストファイルを読み込みました。\n");
		fclose(pFile);
	}
	else
	{
		printf("エラーが発生した為、ファイルを読み込み出来ませんでした");
	}
}

HRESULT CRanking::FontCreate(void)
{

	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 時間情報表示用フォントの生成
	D3DXCreateFont(pDevice, 30, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pRankingFont);

	// 時間情報表示用フォントの生成
	D3DXCreateFont(pDevice, 80, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pRankFont);

	return S_OK;
}

void CRanking::FontUninit(void)
{
	if (m_pRankingFont != NULL)
	{
		m_pRankingFont->Release();
		m_pRankingFont = NULL;
	}
	if (m_pRankFont != NULL)
	{
		m_pRankFont->Release();
		m_pRankFont = NULL;
	}
}
