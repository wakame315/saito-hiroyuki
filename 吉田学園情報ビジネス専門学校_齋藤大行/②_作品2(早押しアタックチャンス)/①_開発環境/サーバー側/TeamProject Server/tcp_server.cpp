//=============================================================================
//
// TCP�T�[�o�[���� [tcp_server.cpp]
// Author : �V����s
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "tcp_server.h"
#include "tcp_client.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTcpListener::CTcpListener()
{
	m_sockServer = -1;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTcpListener::~CTcpListener()
{

}


//=============================================================================
//�I�����菈��
//=============================================================================
void CTcpListener::Release(void)
{
	Close();
	delete this;
}


//=============================================================================
//��������
//=============================================================================
CTcpListener* CTcpListener::Create(int nPortNum)
{
	// TCP�ڑ���t�N���X�̃C���X�^���X����

	CTcpListener *pTcpcserver = new CTcpListener;

	if (pTcpcserver->Init(nPortNum,MAX_ACCEPT_CONNECTION) == false)
	{
		delete pTcpcserver;
		pTcpcserver = NULL;
	}

	return pTcpcserver;
}

//=============================================================================
//�ڑ���t����
//=============================================================================
CTcpClient* CTcpListener::Accept()
{
	struct sockaddr_in client;
	int nAddrLenght = sizeof(client);

	if (m_sockServer < 0) 
	{
		return NULL;
	}

	// �ڑ���t����
	SOCKET sock = accept(m_sockServer, (struct sockaddr*)&client, &nAddrLenght);

	CTcpClient *pTcpclient = CTcpClient::Create(sock);

	return pTcpclient;
}

//=============================================================================
//����������
//=============================================================================
bool CTcpListener::Init(int nPortNum, int nAcceptConnNum)
{
	struct sockaddr_in addr;
	struct sockaddr_in client;

	//�ڑ��p�\�P�b�g�̍쐬
	m_sockServer = socket(AF_INET, SOCK_STREAM, 0);

	//�ڑ���t���̐ݒ�

	addr.sin_family = AF_INET;					//IPv4
	addr.sin_port = htons(SERVER_PORT_NUM);     //�|�[�g�ԍ�
	addr.sin_addr.S_un.S_addr = INADDR_ANY;     //���ׂĂ̐ڑ����󂯕t����

												//�\�b�P�g��IP�A�h���X�ƃ|�[�g�ԍ���ݒ肷��
	bind(m_sockServer, (struct sockaddr*)&addr, sizeof(addr));

	//�ڑ��v����t���J�n����
	listen(m_sockServer, MAX_ACCEPT_CONNECTION);

	//�\�P�b�g�ڑ����󂯕t����i�󂯕t����܂Ńv���O�����̓u���b�N�����j
	int nAddrLenght = sizeof(client);


	printf("�ڑ��҂��ł�\n");

	return true;
}

//=============================================================================
//�I������
//=============================================================================
void CTcpListener::Close()
{
	if (m_sockServer <= 0)
	{
		return;
	}
	//�\�P�b�g�ڑ����N���[�Y
	closesocket(m_sockServer);
	m_sockServer = -1;
}
