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
#include "scene2d.h"
#include "inputkeyboard.h"
#include "player.h"
#include "enemy.h"
#include "explosion.h"
#include "bullet.h"
#include "bg.h"
#include "number.h"
#include "score.h"
#include "title.h"
#include "result.h"
#include "tutorial.h"
#include "sound.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define DEBUG_SCENE2D
#undef  DEBUG_SCENE2D

//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
CRenderer * CManager::m_pRenderer = NULL;
CInputKeyboard * CManager::m_pInputKeyboard = NULL;
CPlayer *CManager::m_pPlayer = NULL;
CTitle *CManager::m_pTitle = NULL;
CResult *CManager::m_pResult = NULL;
int  CManager::m_nEnemy = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CSound * CManager::m_pSound = NULL;
CManager::MODE CManager::m_Mode = MODE_TITLE;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CManager::CManager()
{
	
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
	//�����̏�����
	srand((unsigned int)time(NULL));
	//�����_���[�C���X�^���X����
	m_pRenderer = new CRenderer;
	//�T�E���h�C���X�^���X����
	m_pSound = new CSound;

	// ����������
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		return -1;
	}
	//���̓C���X�^���X����
	m_pInputKeyboard = new CInputKeyboard;
	//���͏���������
	m_pInputKeyboard->Init(hInstance, hWnd);

	//�e�N�X�`���ǂݍ���
	TextureLoad();
	//�T�E���h����������
	m_pSound->Init(hWnd);
	//���[�h�ݒ�
	SetMode(m_Mode);
	

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

	//�L�[�{�[�h���͍X�V
	m_pInputKeyboard->Update();

	//�����_���[�X�V����
	m_pRenderer->Update();

	//��ʑJ��
	switch (m_Mode)
	{
	case MODE_TITLE://�^�C�g��
		//�G���^�[�Ŏ��ɐi��
		if (pKey->GetkeyboardTrigger(DIK_RETURN))
		{	//�`���[�g���A����ʂɑJ��
			SetMode(MODE_TUTORIAL);
		}
		break;
	case MODE_TUTORIAL://�`���[�g���A��
		//�G���^�[�Ŏ��ɐi��
		if (pKey->GetkeyboardTrigger(DIK_RETURN))
		{
			//�Q�[���ɑJ��
			SetMode(MODE_GAME);
			
		}
		break;
	case MODE_GAME://�Q�[��
		//�G���^�[�Ŏ��ɐi��
		if (CEnemy::GetEnemyDesu() >= 15)
		{
			//�Q�[���̃N���A����
			CResult::SetClear(false);
			//���U���g�ɑJ��
			SetMode(MODE_RESULT);
		}
		

		break;
	case MODE_RESULT://���U���g
		//�G���^�[�Ŏ��ɐi��
		if (pKey->GetkeyboardTrigger(DIK_RETURN))
		{	//�^�C�g���ɑJ��
			SetMode(MODE_TITLE);

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
	CPlayer::Load();
	CBullet::Load();
	CExplosion::Load();
	CEnemy::Load();
	CNumber::Load();
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
	CPlayer::Unload();
	CBullet::Unload();
	CExplosion::Unload();
	CEnemy::Unload();
	CNumber::Unload();
}

//=============================================================================
//���[�h�ݒ�֐�
//=============================================================================
void CManager::SetMode(MODE mode)
{
	m_Mode = mode;
	//���[�h���Ƃɐݒ�
	switch (m_Mode)
	{
	case MODE_TITLE://�^�C�g��
			//���U���g�̏I������
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		//�^�C�g������
		m_pTitle = CTitle::Create();
		break;
	case MODE_TUTORIAL://�`���[�g���A��
			//�^�C�g���̏I������
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		//�`���[�g���A������
		m_pTutorial = CTutorial::Create();

		break;
	case MODE_GAME://�Q�[��
			//�`���[�g���A���̏I������
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;
		}

		//2D�|���S���̐���
		CBg::Create();
		//�X�R�A����
		CScore::Create();
		//�G����
		CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (CEnemy::ENEMYTYPE)(rand() % (CEnemy::ENEMY_TYPE_MAX - 2)));
		//���@����
		CPlayer::Create(D3DXVECTOR3(640, 600.0f, 0.0f));
		break;
	case MODE_RESULT://���U���g
		//�G�o�������Z�b�g
		CEnemy::SetNumEnemy(0);
		//�G���������Z�b�g
		CEnemy::SetEnemyDesu(0);
		//���ׂďI������
		CScene::ReleaseAll();
		//���U���g����
		m_pResult = CResult::Create();
		
		break;
	default:
		break;
	}
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
	pManager->Init( hInstance,  hWnd,  bWindow);
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
//�v���C���[�����֐�
//=============================================================================
CPlayer * CManager::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
//���y�����֐�
//=============================================================================
CSound * CManager::GetSound(void)
{
	return m_pSound;
}