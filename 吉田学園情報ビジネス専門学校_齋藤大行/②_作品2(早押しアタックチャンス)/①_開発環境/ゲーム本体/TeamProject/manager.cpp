//=============================================================================
//
// メイン処理 [main.cpp]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
//インクルードファイル
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
// マクロ定義
//*****************************************************************************

#define DEBUG_SCENE2D
#undef  DEBUG_SCENE2D


//=============================================================================
//静的メンバー変数
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
//コンストラクタ
//=============================================================================
CManager::CManager()
{
	m_nGameEndState = 120;
}

//=============================================================================
//デストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
//初期化処理関数
//=============================================================================
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

//=============================================================================
//更新処理関数
//=============================================================================
void CManager::Update(void)
{
	//キーボードのポインタ
	CInputKeyboard *pKey;
	pKey = CManager::GetInputKeyboard();

	//キーボードの更新処理
	m_pInputKeyboard->Update();

	//レンダラー更新処理
	m_pRenderer->Update();

	//画面遷移
	switch (m_Mode)
	{
	case MODE_TITLE://タイトル
		//エンターで次に進む
		if (pKey->GetkeyboardTrigger(DIK_RETURN))
		{
			//チュートリアル画面に遷移
			SetMode(MODE_TUTORIAL);
			//効果音再生
			m_pSound->Play(CSound::SE_SIGNAL);
		
		}
		break;

	case MODE_TUTORIAL://チュートリアル
		//エンターで次に進む
		if (pKey->GetkeyboardTrigger(DIK_RETURN))
		{	
			//タイトルの音楽を停止
			m_pSound->Stop(CSound::BGM_TITLE);
			//効果音を再生
			m_pSound->Play(CSound::SE_SIGNAL);
			//ゲームに遷移
			SetMode(MODE_GAME);
			//ゲーム中の音楽再生
			m_pSound->Play(CSound::BGM_GAME);
		}
		break;

	case MODE_GAME://ゲーム
		//ゲームの判定
		if (pKey->GetkeyboardRelease(DIK_SPACE) == true)
		{  //効果音再生
			m_pSound->Play(CSound::SE_HIT);
			//ゲームを終了状態にする
			m_bGameEnd = true;
			//シーンを1つずつ見ていく
			for (int nCntScene = 0; nCntScene < MAX_POLYGON*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = CScene::GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;
				//NULLチェック
				if (pScene != NULL)
				{	//タイプがDISPLAYTIMEだった時
					if (pScene->GetObjType() == CScene::TYPE_DISPLAYTIME)
					{	
						//ランキングの設定
						m_RankingDeta[0].nRank = CRanking::SetRanking(((CDisplaytime*)pScene)->GetTriggerTime());
						//結果時間の所得
						m_Gettime = ((CDisplaytime*)pScene)->GetTriggerTime();
					}
				}
			}
			CRanking::GetRanking(m_RankingDeta);//ランキングの設定

		}
		//ゲームが終了状態になったら
		if (m_bGameEnd == true)
		{
			//カウントをマイナス
			m_nGameEndState--;

		}
		//0になったら
		if (m_nGameEndState == 0)
		{	//ゲーム中の音楽を停止
			m_pSound->Stop(CSound::BGM_GAME);
			//リザルトに遷移
			SetMode(MODE_RESULT);
			m_pSound->Play(CSound::BGM_RESULT);
		}

		break;
	case MODE_RESULT:
		//エンターで次に進む
		if (pKey->GetkeyboardTrigger(DIK_RETURN))
		{	//効果音再生
			m_pSound->Play(CSound::SE_SIGNAL);
			//リザルトの音楽停止
			m_pSound->Stop(CSound::BGM_RESULT);
			//タイトルに遷移
			SetMode(MODE_TITLE);
			//タイトルの音楽再生
			m_pSound->Play(CSound::BGM_TITLE);
			//カウントを120に設定
			m_nGameEndState = 120;
			
		}
		break;
	default:
		break;
	}
}

//=============================================================================
//描画処理
//=============================================================================
void CManager::Draw(void)
{
	//レンダラー描画処理
	m_pRenderer->Draw();
}

//=============================================================================
//終了処理
//=============================================================================
void CManager::Uninit(void)
{
	//キーボード終了処理
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	//テクスチャアンロード
	TextureUnLoad();
	//フォントアンロード
	CRanking::FontUninit();
	CDisplaytime::FontUninit();

	//レンダラー終了処理
	m_pRenderer->Uninit();
	//レンダラーのデリート
	delete m_pRenderer;
	m_pRenderer = NULL;


}

//=============================================================================
//テクスチャロード
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
//テクスチャアンロード
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
//モード設定関数
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
//ゲーム終了所得関数
//=============================================================================
bool CManager::GetGameEnd(void)
{
	return m_bGameEnd;
}
//=============================================================================
//結果時間所得関数
//=============================================================================
DWORD CManager::GeResultTime(void)
{
	return m_Gettime;
}

//=============================================================================
//音楽所得関数
//=============================================================================
CSound * CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
//モード所得関数
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_Mode;
}

//=============================================================================
//生成処理関数
//=============================================================================
CManager * CManager::Create(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	CManager * pManager;
	pManager = new CManager;
	pManager->Init(hInstance, hWnd, bWindow);
	return pManager;
}

//=============================================================================
//レンダラー所得関数
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
//入力所得関数
//=============================================================================
CInputKeyboard * CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
//ランキングデータ所得関数
//=============================================================================
CRanking::RankingData * CManager::GetRankinData(void)
{
	return m_RankingDeta;
}

//=============================================================================
//プレイヤー所得関数
//=============================================================================
CPolygon * CManager::GetPlayer(void)
{
	return m_pPlayer;
}



