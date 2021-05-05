//********************************************
//�C���N���[�h�t�@�C��
//********************************************
#include "protocol_ranking.h"
#include "tcp_client.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "displaytime.h"


LPD3DXFONT CRanking::m_pRankFont = NULL;//�t�H���g�ւ̃|�C���^
LPD3DXFONT CRanking::m_pRankingFont = NULL;//�t�H���g�ւ̃|�C���^

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

	//winsock������
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);
	if (nErr != 0)
	{
		//���炩�̌����Ŏ��s����
		printf("WSAStartup failed\n");
	}

	CTcpClient * pTcpClient = NULL;

	if (pTcpClient == NULL)
	{
		pTcpClient = CTcpClient::Create(IPADDRESS, SERVER_PORT_NUM);

		if (pTcpClient == NULL)
		{
			//winsock�I������
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

	//winsock�I������
	WSACleanup();
}


int CRanking::SetRanking(int nTime)
{
	CRanking * pRanking;
	pRanking = new CRanking;

	WSADATA wsaData;
	char aSenBuf[BUFFER_NUM];
	char aRecvBuf[BUFFER_NUM];//�����L���O�ݒ�̃��X�|���X����M
	//winsock������
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);
	if (nErr != 0)
	{
		//���炩�̌����Ŏ��s����
		printf("WSAStartup failed\n");
	}

	//tcp����M�N���X�̍쐬
	CTcpClient * pTcpClient = CTcpClient::Create(IPADDRESS, SERVER_PORT_NUM);
	if (pTcpClient == NULL)
	{
		return 0;
	}

	//�����L���O�ݒ胊�N�G�X�g�̑��M

	//��o�C�g�ځFCOMMAND_TYPE_SET_RANKING

	pRanking->ReadFile();

	aSenBuf[0] = COMMAND_TYPE_SET_RANKING;

	//2�`5�o�C�g�ځF�N���A�^�C����ݒ�i�G���f�B�A���ϊ���htonl�֐����g�p�j
	nTime = htonl(nTime);
	memcpy(&aSenBuf[1], &nTime, sizeof(int));
	//6�`13�o�C�g�ځF���O��ݒ�
	memcpy(&aSenBuf[5], &pRanking->m_aName, MAX_NAME);
	//���M
	pTcpClient->Send(aSenBuf, 20);

	memset(aRecvBuf, 0, sizeof(aRecvBuf));

	pTcpClient->Recv(aRecvBuf, sizeof(aRecvBuf));

	//�ؒf����
	pTcpClient->Release();

	//winsock�I������
	WSACleanup();

	return aRecvBuf[0];
}





void CRanking::Ranking(RankingData * RankingData, int Rank)
{
	char str[512];

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		RECT Rankingrect = { 100, 60 * (nCnt + 1), SCREEN_WIDTH, SCREEN_HEIGHT };


		sprintf(str, "����:%d ���O:%s ���ʎ���:%.3f�b\n", nCnt + 1, RankingData[nCnt].aName, (float)RankingData[nCnt].nClearTime / 1000.0f);
		// �e�L�X�g�`��
		m_pRankingFont->DrawText(NULL, str, -1, &Rankingrect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0, 0, 0));
	}

	RECT MyRankingrect = { 575, 250 , SCREEN_WIDTH, SCREEN_HEIGHT };

	if (CManager::GeResultTime() == NULL)
	{
		sprintf(str, "����:����t��");
	}
	else
	{
		if (Rank >= 11)
		{
			sprintf(str, "����:%d\n���ʎ���:%.3f�b", Rank, CManager::GeResultTime() / 1000.0f);

		}
		else
		{
			sprintf(str, "����:%d", Rank);
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

		printf("�e�L�X�g�t�@�C����ǂݍ��݂܂����B\n");
		fclose(pFile);
	}
	else
	{
		printf("�G���[�����������ׁA�t�@�C����ǂݍ��ݏo���܂���ł���");
	}
}

HRESULT CRanking::FontCreate(void)
{

	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���ԏ��\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 30, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pRankingFont);

	// ���ԏ��\���p�t�H���g�̐���
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
