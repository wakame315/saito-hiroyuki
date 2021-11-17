//=============================================================================
//
// ���C����` [main.h]
// Author : �V����s
//
//=============================================================================

//=============================================================================
//��d�C���N���[�h�h�~
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include<WinSock2.h>
#include<windows.h>
#include<dinput.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<stdint.h>
#include"d3dx9.h"

//=============================================================================
// ���C�u�����t�@�C�������N
//=============================================================================
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "ws2_32.lib")
//=============================================================================
//�}�N����`
//=============================================================================
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)	
#define SCREEN_WIDTH	(1280)								//�E�B���h�T�C�Y��
#define SCREEN_HEIGHT	(720)								//�E�B���h�T�C�Y�c
#define NUM_VERTEX (4)										//���_��
#define NUM_POLYGON (2)										//�|���S����
#define MAX_POLYGON (1024)									//�|���S���̍ő吔
#define TEXTURE_WIDTH  (75)									//�e�N�X�`���̉��T�C�Y
#define TEXTURE_HEIGHT (75)									//�e�N�X�`���̏c�T�C�Y
#define NONE_CLO 255										//�J���[�̏����l

#define TEXTURE_NAME1 "Resource/TEXTURE/signal.png"			//���}
#define TEXTURE_NAME2 "Resource/TEXTURE/�o�c�}�[�N.png"		//����t��
#define TEXTURE_NAME3 "Resource/TEXTURE/Background.png"		//�w�i
#define TEXTURE_NAME4 "Resource/TEXTURE/pose_woman.png"		//�L�����N�^�[
#define TEXTURE_NAME5 "Resource/TEXTURE/target.png"			//�I
#define TEXTURE_NAME6 "Resource/TEXTURE/title.png"			//�^�C�g��
#define TEXTURE_NAME7 "Resource/TEXTURE/title_rogo2.png"	//�^�C�g��logo
#define TEXTURE_NAME8 "Resource/TEXTURE/explain_rules.png"	//�`���[�g���A��
#define TEXT_NEMA1    "Resource/TEXT/NAME.txt"				//���O�ǂݍ��ݗpFILE

			
#define PRIORITY_MAX 5										//�v���C�I���e�B�ő吔
#define POLYGON_SIZE_X (200)								//�|���S���T�C�Y��
#define POLYGON_SIZE_Y (200)								//�|���S���T�C�Y�c
#define MAX_SIGNAL (2)										//���}�̍ő吔
#define MAX_RAND (10)										//�����ő�l
#define MIN_RAND (5)										//�����Œ�l
#define MAX_TIME (10000)									//���ԍő吔
#define MIN_TIME (5000)										//���ԍŒᐔ

#define MAX_RANKING (10)									//�����L���O��
#define MAX_NAME 15											// ���O�T�C�Y(������)

#define SERVER_PORT_NUM 12345								//�|�[�g�ԍ�
#define MAX_ACCEPT_CONNECTION 5								//�ő�ڑ���
#define BUFFER_NUM 1024										//�f�[�^�ő吔
//#undef _DEBUG


//=============================================================================
// �O���錾
//=============================================================================
class CRenderer;
class CScene;

//�v���g�^�C�v�錾
int GetFPS(void);


//=============================================================================
//�\����
//=============================================================================
typedef struct
{
	D3DXVECTOR3 Pos;
	float rhw;
	D3DCOLOR clo;
	D3DXVECTOR2 tex;

}VERTEX_2D;

#endif