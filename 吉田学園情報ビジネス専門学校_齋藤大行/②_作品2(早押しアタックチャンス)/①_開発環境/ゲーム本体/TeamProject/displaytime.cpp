//=============================================================================
//
// �\�����ԏ��� [displaytime.cpp]
// Author :�V����s
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "displaytime.h"
#include "manager.h"
#include "input.h"
#include "inputkeyboard.h"
#include "renderer.h"
#include "main.h"

//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
LPD3DXFONT CDisplaytime::m_pTimeFont = NULL;//�t�H���g�ւ̃|�C���^
LPD3DXFONT CDisplaytime::m_pMissFont = NULL;//�t�H���g�ւ̃|�C���^

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CDisplaytime::CDisplaytime() :CScene(4)
{
	m_dwGameStartTime = 0;
	m_dwTriggerGameTime = 0;
	m_dwTriggerTime = 0;
	m_dwGameTime = 0;
	m_dwGamePressStartTime = 0;
	m_bCntTimeUse = false;
	m_bDraw = false;
	m_bPressUse = false;
	m_bStartTime = false;
	m_nStop = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CDisplaytime::~CDisplaytime()
{
	m_bCntTimeUse = false;
	m_bDraw = false;
}

//=============================================================================
//�����������֐�
//=============================================================================
HRESULT CDisplaytime::Init(void)
{
	m_dwGameStartTime = 0;
	m_dwTriggerGameTime = 0;
	m_dwTriggerTime = 0;
	m_dwGameTime = 0;
	m_dwGamePressStartTime = 0;
	m_bCntTimeUse = false;
	m_bDraw = false;
	m_bPressUse = false;
	m_nStop = 0;

	return S_OK;
}

//=============================================================================
//�I�������֐�
//=============================================================================
void CDisplaytime::Uninit(void)
{
	//�I�u�W�F�N�g�j��
	Release();
}

//=============================================================================
//�X�V�����֐�
//=============================================================================
void CDisplaytime::Update(void)
{
	CInputKeyboard *pKey;
	pKey = CManager::GetInputKeyboard();
	

	switch (CManager::GetMode())
	{
	case CManager::MODE_TITLE:
		
		break;

	case CManager::MODE_TUTORIAL:

	
		break;

	case CManager::MODE_GAME:
		
		if (!m_bStartTime)
		{
			m_dwGameStartTime = timeGetTime();
			m_bStartTime = true;
		}

for (int nCntScene = 0; nCntScene < MAX_POLYGON*PRIORITY_MAX; nCntScene++)//�V�[���̏���
	{
		CScene *pScene = GetScene(nCntScene);
		CScene2d *pScene2d = (CScene2d*)pScene;//�V�[���̃_�u���|�C���^
		if (pScene != NULL)
		{
			if (pScene->GetObjType() == TYPE_POLYGON)//�I�u�W�F�N�g���|���S���̏ꍇ
			{
				if (((CPolygon*)pScene)->GetUse() == true && ((CPolygon*)pScene)->GetTexSignal() == CPolygon::TEX_SIGNAL_GO)//���}�̃|���S�����I���̏ꍇ
				{
					if (m_bCntTimeUse == false)//���}���\������Ă܂����ʎ��Ԃ��J�E���g���ĂȂ��Ƃ�
					{
						if (m_nStop == 0)//��x�������l���Ƃ邽��
						{
							m_dwTriggerTime = m_dwGameTime;//���}���\�����ꂽ�u�Ԃ̎��Ԃ�����
							m_bCntTimeUse = true;//���}���\������Ă���̎��Ԃ��J�E���g���J�n
							m_nStop = 1;//1�����ēǂ܂�Ȃ��悤�ɂ���
						}
					}
					else if (m_bCntTimeUse == true)//���ʎ��Ԃ̃J�E���g�����Ă���Ƃ�
					{
						if (pKey->GetkeyboardRelease(DIK_SPACE) == true)//SPACE�L�[�𗣂�����
						{
							m_bPressUse = true;
							m_bCntTimeUse = false;//���ʎ��Ԃ̃J�E���g���~�߂�
							m_bDraw = true;//���ʎ��Ԃ̕\��
						}
					}
				}
				else if (((CPolygon*)pScene)->GetTexSignal() == CPolygon::TEX_SIGNAL_GO && ((CPolygon*)pScene)->GetUse() == false)//���}�̃|���S�����I�t�̏ꍇ
				{

					if (pKey->GetkeyboardRelease(DIK_SPACE) == true)//SPACE�L�[�𗣂�����
					{
						m_bPressUse = true;
						m_bCntTimeUse = false;//���ʎ��Ԃ̃J�E���g�𓮂��Ȃ��悤�ɂ���
						m_bDraw = true;//���ʎ��Ԃ̕\��
						for (int nCntScene = 0; nCntScene < MAX_POLYGON*PRIORITY_MAX; nCntScene++)//�V�[���̏���
						{
							CScene *pScene = GetScene(nCntScene);
							CScene2d *pScene2d = (CScene2d*)pScene;//�V�[���̃_�u���|�C���^
							if (pScene != NULL)
							{
								if (pScene->GetObjType() == TYPE_POLYGON)//�I�u�W�F�N�g���|���S���̏ꍇ
								{
									if (((CPolygon*)pScene)->GetTexSignal() == CPolygon::TEX_SIGNAL_MISS)//����t���̃|���S���̏ꍇ
									{
										((CPolygon*)pScene)->SetbUse(true);//����t���̃|���S����\������
									}
								}
							}
						}
					}
				}

			}
		}
	}

	if (pKey->GetkeyboardTrigger(DIK_SPACE) == true)
	{
   		m_dwGameStartTime = timeGetTime();
	}


	

	if (pKey->Getkeyboardpress(DIK_SPACE) == true)
	{
		m_dwGameTime = timeGetTime() - m_dwGameStartTime;
	}


	
	if (m_bCntTimeUse == true)
	{
		m_dwTriggerGameTime = m_dwGameTime - m_dwTriggerTime;
	}
		
	break;

	case CManager::MODE_RESULT:

		break;
	}
	
} 

//=============================================================================
//�`�揈���֐�
//=============================================================================
void CDisplaytime::Draw(void)
{
	//���ԕ\��
	//DrawTime(m_dwGameTime);

	if (m_bDraw == true)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON*PRIORITY_MAX; nCntScene++)
		{
			CScene *pScene = GetScene(nCntScene);
			CScene2d *pScene2d = (CScene2d*)pScene;
			if (pScene != NULL)
			{
				if (pScene->GetObjType() == TYPE_POLYGON)
				{
					if (((CPolygon*)pScene)->GetUse() == true && ((CPolygon*)pScene)->GetTexSignal() == CPolygon::TEX_SIGNAL_GO)
					{
						TriggerTime(m_dwTriggerGameTime);
					}
					else if (((CPolygon*)pScene)->GetUse() == false && ((CPolygon*)pScene)->GetTexSignal() == CPolygon::TEX_SIGNAL_GO)
					{
						DrawMiss();
					}
				}
			}
		}
	}
}

//=============================================================================
//�o�ߎ��ԕ`��p�֐�
//=============================================================================
void CDisplaytime::DrawTime(DWORD time)
{
	
		RECT rect = { SCREEN_WIDTH / 2.5, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		char str[256];

		sprintf(str, "�o�ߎ���:%.3f�b\n", (float)time / 1000.0f);

		// �e�L�X�g�`��
		m_pTimeFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	
}

//=============================================================================
//���ʎ��ԕ`��֐�
//=============================================================================
void CDisplaytime::TriggerTime(DWORD TriggerTime)
{
		RECT rect = { SCREEN_WIDTH / 2.5, 100, SCREEN_WIDTH, SCREEN_HEIGHT };
		char str[256];

		sprintf(str, "���ʎ���:%.3f�b\n", (float)TriggerTime / 1000.0f);

		// �e�L�X�g�`��
		m_pTimeFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0, 0, 0));
}

//=============================================================================
//����t���`��֐�
//=============================================================================
void CDisplaytime::DrawMiss(void)
{
	RECT rect = { SCREEN_WIDTH / 2.5, 100, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	sprintf(str, "����:����t��");

	// �e�L�X�g�`��
	m_pMissFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0, 0, 0));
}

//=============================================================================
//�o�ߎ��ԏ����֐�
//=============================================================================
DWORD CDisplaytime::GetTime(void)
{
	return m_dwGameTime;
}

//=============================================================================
//���ʎ��ԏ����֐�
//=============================================================================
DWORD CDisplaytime::GetTriggerTime(void)
{
	return m_dwTriggerGameTime;
}

//=============================================================================
//�t�H���g���������֐�
//=============================================================================
HRESULT CDisplaytime::FontCreate(void)
{

	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���ԏ��\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 50, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pTimeFont);

	// ����t�����\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 50, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pMissFont);
	
	return S_OK;
}

//=============================================================================
//�t�H���g�I�������֐�
//=============================================================================
void CDisplaytime::FontUninit(void)
{
	if (m_pTimeFont != NULL)
	{
		m_pTimeFont->Release();
		m_pTimeFont = NULL;
	}
	if (m_pMissFont != NULL)
	{
		m_pMissFont->Release();
		m_pMissFont = NULL;
	}
}

//=============================================================================
//���������֐�
//=============================================================================
CDisplaytime * CDisplaytime::Create()
{
	CDisplaytime * pDisplaytime;
	pDisplaytime = new CDisplaytime;
	pDisplaytime->Init();
	pDisplaytime->SetObjType(TYPE_DISPLAYTIME);
	return pDisplaytime;
}

