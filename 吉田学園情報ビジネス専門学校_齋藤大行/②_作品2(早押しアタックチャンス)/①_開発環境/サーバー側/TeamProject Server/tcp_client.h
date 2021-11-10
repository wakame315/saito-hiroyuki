//=============================================================================
//
// TCP�N���C�A���g��` [TCP_client.h]
// Author :�V����s
//
//=============================================================================
#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_
#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include<WinSock2.h>
#include<stdio.h>

//=============================================================================
//�}�N����`
//=============================================================================
#define SERVER_PORT_NUM 12345
#define MAX_ACCEPT_CONNECTION 5
#define BUFFER_NUM 1024

//=============================================================================
//�N���X��`
//=============================================================================
class CTcpClient
{
public:
	CTcpClient();														 //�R���X�g���N�^
	~CTcpClient();														 //�f�X�g���N�^
	static CTcpClient *Create(const char*pHostName, int nPortNum);		 //��������
	static CTcpClient *Create(SOCKET sock);								 //��������(�A�N�Z�v�g�ɂ��ڑ�)
	void Release(void);													 //�I�����菈��
	bool Init(const char *pHostName, int nPortNum);						 //����������
	bool Init(SOCKET sock);												 //����������(�A�N�Z�v�g�ɂ��ڑ�)
	int Send(char * pSendData, int nSendDataSize);						 //���M����
	int Recv(char *pRecvBuf, int nRecvBuffSize);						 //��M����

	void Close();														 //�I������

private:
	SOCKET m_sock;
};


#endif 
