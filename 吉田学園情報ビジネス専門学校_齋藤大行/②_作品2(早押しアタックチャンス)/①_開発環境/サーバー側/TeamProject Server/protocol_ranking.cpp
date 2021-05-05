//********************************************
//�C���N���[�h�t�@�C��
//********************************************
#include "protocol_ranking.h"
#include "tcp_client.h"
#include "main.h"

void GetRanking(RankingData * pRankingData)
{
	WSADATA wsaData;
	char aRecvBuf[128];
	char aSendBuf[128];

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

	//winsock�I������
	WSACleanup();
}



int SetRanking(int nTime)
{
	WSADATA wsaData;

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
	char aSenBuf[128];
	aSenBuf[0] = COMMAND_TYPE_SET_RANKING;

	//2�`5�o�C�g�ځF�N���A�^�C����ݒ�i�G���f�B�A���ϊ���htonl�֐����g�p�j
	nTime = htonl(nTime);
	memcpy(&aSenBuf[1], &nTime, sizeof(int));
	//6�`13�o�C�g�ځF���O��ݒ�
	memcpy(&aSenBuf[5], &"���O", MAX_NAME);
	//���M
	pTcpClient->Send(aSenBuf, 13);

	//�����L���O�ݒ�̃��X�|���X����M
	char aRecvBuf[128];
	memset(aRecvBuf, 0, sizeof(aRecvBuf));
	pTcpClient->Recv(aRecvBuf, sizeof(aRecvBuf));

	//�ؒf����
	pTcpClient->Release();

	//winsock�I������
	WSACleanup();

	return aRecvBuf[0];
}
