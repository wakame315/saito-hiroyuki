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

#define DEBUG_SCENE2D
#undef  DEBUG_SCENE2D

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
CManager::CManager()
{
	m_nGameEndState = 120;
	m_nDisTimeinit = 0;
}

CManager::~CManager()
{
}

HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{

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
	CRanking::FontCreate();
	CDisplaytime::FontCreate();
	SetMode(m_Mode);

	m_pSound->Play(CSound::BGM_TITLE);
	return S_OK;
}


void CManager::Update(void)
{
	CInputKeyboard *pKey;

	pKey = CManager::GetInputKeyboard();

	m_pInputKeyboard->Update();

	//レンダラー更新処理
	m_pRenderer->Update();

	switch (m_Mode)
	{
	case MODE_TITLE:
		//m_pSound->Play(CSound::BGM_TITLE);
		if (pKey->GetkeyboardTrigger(DIK_RETURN))
		{
			SetMode(MODE_TUTORIAL);
			m_pSound->Play(CSound::SE_SIGNAL);
		
		}
		break;

	case MODE_TUTORIAL:
		
		if (pKey->GetkeyboardTrigger(DIK_RETURN))
		{	
			m_pSound->Stop(CSound::BGM_TITLE);
			m_pSound->Play(CSound::SE_SIGNAL);
			SetMode(MODE_GAME);
			m_pSound->Play(CSound::BGM_GAME);
		}
		break;

	case MODE_GAME:
		
		if (pKey->GetkeyboardRelease(DIK_SPACE) == true)
		{
			m_pSound->Play(CSound::SE_HIT);
			m_bGameEnd = true;

			for (int nCntScene = 0; nCntScene < MAX_POLYGON*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = CScene::GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;
				if (pScene != NULL)
				{	
					if (pScene->GetObjType() == CScene::TYPE_DISPLAYTIME)
					{	
						m_RankingDeta[0].nRank = CRanking::SetRanking(((CDisplaytime*)pScene)->GetTriggerTime());
						m_Gettime = ((CDisplaytime*)pScene)->GetTriggerTime();
					}
					else if (pScene->GetObjType() == CScene::TYPE_BG)
					{
						if (((CBg*)pScene)->GetBG() == CBg::BG_TYPE3)
						{
							if (((CScene2d*)pScene)->GetDraw() == false)
							{
								((CScene2d*)pScene)->SetDraw(true);
							}
						}
					}
				}
			}
			CRanking::GetRanking(m_RankingDeta);

		}
		if (m_bGameEnd == true)
		{
			m_nGameEndState--;

		}
		if (m_nGameEndState == 0)
		{
			m_pSound->Stop(CSound::BGM_GAME);
			SetMode(MODE_RESULT);
			m_pSound->Play(CSound::BGM_RESULT);
		}

		break;
	case MODE_RESULT:
		
		if (pKey->GetkeyboardTrigger(DIK_RETURN))
		{
			m_pSound->Play(CSound::SE_SIGNAL);
			m_pSound->Stop(CSound::BGM_RESULT);
			SetMode(MODE_TITLE);
			m_pSound->Play(CSound::BGM_TITLE);
			m_nGameEndState = 120;
			
			
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
	CRanking::FontUninit();
	CDisplaytime::FontUninit();

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
	CPolygon::Load();
}

void CManager::TextureUnLoad(void)
{
	CTitle::Unload();
	CTutorial::Unload();
	CResult::Unload();
	CBg::Unload();
	CPolygon::Unload();
}

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

bool CManager::GetGameEnd(void)
{
	return m_bGameEnd;
}

DWORD CManager::GeResultTime(void)
{
	return m_Gettime;
}

CSound * CManager::GetSound(void)
{
	return m_pSound;
}

CManager::MODE CManager::GetMode(void)
{
	return m_Mode;
}

CManager * CManager::Create(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	CManager * pManager;
	pManager = new CManager;
	pManager->Init(hInstance, hWnd, bWindow);
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

CRanking::RankingData * CManager::GetRankinData(void)
{
	return m_RankingDeta;
}



CPolygon * CManager::GetPlayer(void)
{
	return m_pPlayer;
}



