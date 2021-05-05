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
#include "life.h"
#include "tutorial.h"
#include "sound.h"

#define DEBUG_SCENE2D
#undef  DEBUG_SCENE2D

CRenderer * CManager::m_pRenderer = NULL;
CInputKeyboard * CManager::m_pInputKeyboard = NULL;
CPlayer *CManager::m_pPlayer = NULL;
CTitle *CManager::m_pTitle = NULL;
CResult *CManager::m_pResult = NULL;
int  CManager::m_nEnemy = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CSound * CManager::m_pSound = NULL;
CManager::MODE CManager::m_Mode = MODE_TITLE;

CManager::CManager()
{
	
}

CManager::~CManager()
{
}

HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	
	srand((unsigned int)time(NULL));
	m_pRenderer = new CRenderer;
	
	m_pSound = new CSound;

	// 初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		return -1;
	}

	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	
	TextureLoad();
	m_pSound->Init(hWnd);
	SetMode(m_Mode);
	

	return S_OK;
}


void CManager::Update(void)
{
	CInputKeyboard *pKey;
	pKey = CManager::GetInputKeyboard();

	m_nEnemy = CEnemy::GetNumEnemy();

	


	m_pInputKeyboard->Update();

	//レンダラー更新処理
	m_pRenderer->Update();

	switch (m_Mode)
	{
	case MODE_TITLE:
		if (pKey->GetkeyboardTrigger(DIK_RETURN))
		{
			SetMode(MODE_TUTORIAL);
		}
		break;
	case MODE_TUTORIAL:

		if (pKey->GetkeyboardTrigger(DIK_RETURN))
		{
			
			SetMode(MODE_GAME);
			
		}
		break;
	case MODE_GAME:
		if (CEnemy::GetEnemyDesu() >= 15)
		{
			CResult::SetClear(false);
			SetMode(MODE_RESULT);
		}
		

		break;
	case MODE_RESULT:
		if (pKey->GetkeyboardTrigger(DIK_RETURN))
		{
			SetMode(MODE_TITLE);

		}
		break;
	default:
		break;
	}
}

void CManager::Draw(void)
{
	//レンダラー描画処理
	m_pRenderer->Draw();
}

void CManager::Uninit(void)
{	
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	TextureUnLoad();
	

	//レンダラー終了処理
	m_pRenderer->Uninit();

	delete m_pRenderer;
	m_pRenderer = NULL;

	
}

void CManager::TextureLoad(void)
{
	CTitle::Load();
	CTutorial::Load();
	CResult::Load();
	CBg::Load();
	CPlayer::Load();
	CLife::Load();
	CBullet::Load();
	CExplosion::Load();
	CEnemy::Load();
	CNumber::Load();
}

void CManager::TextureUnLoad(void)
{
	CTitle::Unload();
	CTutorial::Unload();
	CResult::Unload();
	CBg::Unload();
	CPlayer::Unload();
	CLife::Unload();
	CBullet::Unload();
	CExplosion::Unload();
	CEnemy::Unload();
	CNumber::Unload();
}

void CManager::SetMode(MODE mode)
{
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

		//2Dポリゴンの生成
		CBg::Create();
		//CLife::Create();
		CScore::Create();
		CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (CEnemy::ENEMYTYPE)(rand() % (CEnemy::ENEMY_TYPE_MAX - 2)));
		CPlayer::Create(D3DXVECTOR3(640, 600.0f, 0.0f));
		break;
	case MODE_RESULT:
		CEnemy::SetNumEnemy(0);
		CEnemy::SetEnemyDesu(0);
		CScene::ReleaseAll();
		m_pResult = CResult::Create();
		
		break;
	default:
		break;
	}
}

CManager::MODE CManager::GetMode(void)
{
	return m_Mode;
}

CManager * CManager::Create(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	CManager * pManager;
	pManager = new CManager;
	pManager->Init( hInstance,  hWnd,  bWindow);
	return pManager;
}

CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

CInputKeyboard * CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

CPlayer * CManager::GetPlayer(void)
{
	return m_pPlayer;
}

CSound * CManager::GetSound(void)
{
	return m_pSound;
}