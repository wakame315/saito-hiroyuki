//=============================================================================
//
// ���C������ [main.cpp]
// Author : �V����s
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================

#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "inputkeyboard.h"
#include "polygon.h"
#include "bg.h"
#include "displaytime.h"
#include "polygon.h"
#include "protocol_ranking.h"
#include "displaytime.h"
#include "title.h"
#include "result.h"
#include "tutorial.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define DEBUG_SCENE2D
#undef  DEBUG_SCENE2D


//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
CRenderer * CManager::m_pRenderer = NULL;
CInputKeyboard * CManager::m_pInputKeyboard = NULL;
CTitle *CManager::m_pTitle = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CResult *CManager::m_pResult = NULL;
CManager::MODE CManager::m_Mode = MODE_TITLE;
DWORD CManager::m_Gettime = 0;
CRanking::RankingData  CManager::m_RankingDeta[MAX_RANKING] = {};
bool CManager::m_bGameEnd = false;
CSound * CManager::m_pSound;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CManager::CManager()
{
	m_nGameEndState = 120;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
//�����������֐�
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{

	m_pRenderer = new CRenderer;
	
	m_pSound = new CSound;

	// ����������
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		return -1;
	}
	
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	TextureLoad();
	m_pSound->Init(hWnd);
	CRanking::FontCreate();
	CDisplaytime::FontCreate();
	SetMode(m_Mode);

	m_pSound->Play(CSound::BGM_TITLE);
	return S_OK;
}

//=============================================================================
//�X�V�����֐�
//=============================================================================
void CManager::Update(void)
{
	//�L�[�{�[�h�̃|�C���^
	CInputKeyboard *pKey;
	pKey = CManager::GetInputKeyboard();

	//�L�[�{�[�h�̍X�V����
	m_pInputKeyboard->Update();

	//�����_���[�X�V����
	m_pRenderer->Update();

	//��ʑJ��
	switch (m_Mode)
	{
	case MODE_TITLE://�^�C�g��
		//�G���^�[�Ŏ��ɐi��
		if (pKey->GetkeyboardTrigger(DIK_RETURN))
		{
			//�`���[�g���A����ʂɑJ��
			SetMode(MODE_TUTORIAL);
			//���ʉ��Đ�
			m_pSound->Play(CSound::SE_SIGNAL);
		
		}
		break;

	case MODE_TUTORIAL://�`���[�g���A��
		//�G���^�[�Ŏ��ɐi��
		if (pKey->GetkeyboardTrigger(DIK_RETURN))
		{	
			//�^�C�g���̉��y���~
			m_pSound->Stop(CSound::BGM_TITLE);
			//���ʉ����Đ�
			m_pSound->Play(CSound::SE_SIGNAL);
			//�Q�[���ɑJ��
			SetMode(MODE_GAME);
			//�Q�[�����̉��y�Đ�
			m_pSound->Play(CSound::BGM_GAME);
		}
		break;

	case MODE_GAME://�Q�[��
		//�Q�[���̔���
		if (pKey->GetkeyboardRelease(DIK_SPACE) == true)
		{  //���ʉ��Đ�
			m_pSound->Play(CSound::SE_HIT);
			//�Q�[�����I����Ԃɂ���
			m_bGameEnd = true;
			//�V�[����1�����Ă���
			for (int nCntScene = 0; nCntScene < MAX_POLYGON*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = CScene::GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;
				//NULL�`�F�b�N
				if (pScene != NULL)
				{	//�^�C�v��DISPLAYTIME��������
					if (pScene->GetObjType() == CScene::TYPE_DISPLAYTIME)
					{	
						//�����L���O�̐ݒ�
						m_RankingDeta[0].nRank = CRanking::SetRanking(((CDisplaytime*)pScene)->GetTriggerTime());
						//���ʎ��Ԃ̏���
						m_Gettime = ((CDisplaytime*)pScene)->GetTriggerTime();
					}
				}
			}
			CRanking::GetRanking(m_RankingDeta);//�����L���O�̐ݒ�

		}
		//�Q�[�����I����ԂɂȂ�����
		if (m_bGameEnd == true)
		{
			//�J�E���g���}�C�i�X
			m_nGameEndState--;

		}
		//0�ɂȂ�����
		if (m_nGameEndState == 0)
		{	//�Q�[�����̉��y���~
			m_pSound->Stop(CSound::BGM_GAME);
			//���U���g�ɑJ��
			SetMode(MODE_RESULT);
			m_pSound->Play(CSound::BGM_RESULT);
		}

		break;
	case MODE_RESULT:
		//�G���^�[�Ŏ��ɐi��
		if (pKey->GetkeyboardTrigger(DIK_RETURN))
		{	//���ʉ��Đ�
			m_pSound->Play(CSound::SE_SIGNAL);
			//���U���g�̉��y��~
			m_pSound->Stop(CSound::BGM_RESULT);
			//�^�C�g���ɑJ��
			SetMode(MODE_TITLE);
			//�^�C�g���̉��y�Đ�
			m_pSound->Play(CSound::BGM_TITLE);
			//�J�E���g��120�ɐݒ�
			m_nGameEndState = 120;
			
		}
		break;
	default:
		break;
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CManager::Draw(void)
{
	//�����_���[�`�揈��
	m_pRenderer->Draw();
}

//=============================================================================
//�I������
//=============================================================================
void CManager::Uninit(void)
{
	//�L�[�{�[�h�I������
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	//�e�N�X�`���A�����[�h
	TextureUnLoad();
	//�t�H���g�A�����[�h
	CRanking::FontUninit();
	CDisplaytime::FontUninit();

	//�����_���[�I������
	m_pRenderer->Uninit();
	//�����_���[�̃f���[�g
	delete m_pRenderer;
	m_pRenderer = NULL;


}

//=============================================================================
//�e�N�X�`�����[�h
//=============================================================================
void CManager::TextureLoad(void)
{	
	CTitle::Load();
	CTutorial::Load();
	CResult::Load();
	CBg::Load();
	CPolygon::Load();
}

//=============================================================================
//�e�N�X�`���A�����[�h
//=============================================================================
void CManager::TextureUnLoad(void)
{
	CTitle::Unload();
	CTutorial::Unload();
	CResult::Unload();
	CBg::Unload();
	CPolygon::Unload();
}

//=============================================================================
//���[�h�ݒ�֐�
//=============================================================================
void CManager::SetMode(MODE mode)
{

	CInputKeyboard *pKey;

	pKey = CManager::GetInputKeyboard();

	m_Mode = mode;
	switch (m_Mode)
	{
	case MODE_TITLE:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
			
		}
	
		m_pTitle = CTitle::Create();
		CDisplaytime::Create();
		break;

	case MODE_TUTORIAL:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		m_pTutorial = CTutorial::Create();
	
		break;

	case MODE_GAME:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;
		}

		
		CBg::Create();
		CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, 0.0f), D3DXVECTOR3(POLYGON_SIZE_X + 100, POLYGON_SIZE_Y, 0.0f), CPolygon::TEX_SIGNAL_GO);
		CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, 0.0f), D3DXVECTOR3(POLYGON_SIZE_X, POLYGON_SIZE_Y, 0.0f), CPolygon::TEX_SIGNAL_MISS);

		break;
	case MODE_RESULT:

			CScene::ReleaseAll();
			m_pResult = CResult::Create();
			m_bGameEnd = false;

		break;
	default:
		break;
	}
}

//=============================================================================
//�Q�[���I�������֐�
//=============================================================================
bool CManager::GetGameEnd(void)
{
	return m_bGameEnd;
}
//=============================================================================
//���ʎ��ԏ����֐�
//=============================================================================
DWORD CManager::GeResultTime(void)
{
	return m_Gettime;
}

//=============================================================================
//���y�����֐�
//=============================================================================
CSound * CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
//���[�h�����֐�
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_Mode;
}

//=============================================================================
//���������֐�
//=============================================================================
CManager * CManager::Create(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	CManager * pManager;
	pManager = new CManager;
	pManager->Init(hInstance, hWnd, bWindow);
	return pManager;
}

//=============================================================================
//�����_���[�����֐�
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
//���͏����֐�
//=============================================================================
CInputKeyboard * CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
//�����L���O�f�[�^�����֐�
//=============================================================================
CRanking::RankingData * CManager::GetRankinData(void)
{
	return m_RankingDeta;
}

//=============================================================================
//�v���C���[�����֐�
//=============================================================================
CPolygon * CManager::GetPlayer(void)
{
	return m_pPlayer;
}



