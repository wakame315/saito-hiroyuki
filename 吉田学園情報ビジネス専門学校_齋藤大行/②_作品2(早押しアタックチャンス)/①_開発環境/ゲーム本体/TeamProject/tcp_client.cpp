//=============================================================================
//
// TCP�N���C�A���g���� [tcp_client.cpp]
// Author : �V����s
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "tcp_client.h"

//=============================================================================
//�C���X�g���N�^
//=============================================================================
CTcpClient::CTcpClient()
{
	m_sock = -1;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTcpClient::~CTcpClient()
{

}

//=============================================================================
//���������֐�
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
//�����������֐�
//=============================================================================
bool CTcpClient::Init(const char *pHostName, int nPortNum)
{
	//�ڑ��\�P�b�g�̐���
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sock == INVALID_SOCKET)
	{
		/*printf("socket:%d\n", WSAGetLastError());
		return 1;*/
		return false;
	}

	struct sockaddr_in addr;

	//�ڑ���̏��̐ݒ�
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPortNum);
	addr.sin_addr.S_un.S_addr = inet_addr(pHostName);

	//�T�[�o�[�ɐڑ�����
	if (connect(m_sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{
		printf("connect:%d\n", WSAGetLastError());
		//�\�P�b�g�ڑ����N���[�Y
		closesocket(m_sock);
		return false;
	}
	return true;
}


//=============================================================================
//���M�����֐�
//=============================================================================
int CTcpClient::Send(char *pSendData, int nSendDataSize)
{
	if (m_sock <= 0)
	{
		//�ڑ��N���[�Y
		CTcpClient::Close();
	}

	nSendDataSize = send(m_sock, pSendData, nSendDataSize, 0);

	return nSendDataSize;
}


//=============================================================================
//��M�����֐�
//=============================================================================
int CTcpClient::Recv(char *pRecvBuf, int nRecvBuffSize)
{
	if (m_sock <= 0)
	{
		//�ڑ��N���[�Y
		CTcpClient::Close();
	}
	nRecvBuffSize = recv(m_sock, pRecvBuf, nRecvBuffSize, 0);

	return nRecvBuffSize;
}


//=============================================================================
//�I�������֐�
//=============================================================================
void CTcpClient::Close()
{
	if (m_sock <= 0)
	{
		return;
	}
	//�\�P�b�g�ڑ����N���[�Y
	closesocket(m_sock);
	m_sock = -1;
}
