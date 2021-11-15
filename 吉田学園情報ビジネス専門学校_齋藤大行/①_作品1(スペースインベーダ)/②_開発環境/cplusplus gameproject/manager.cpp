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
//マクロ定義
//=============================================================================
#define DEBUG_SCENE2D
#undef  DEBUG_SCENE2D

//=============================================================================
//静的メンバー変数
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
//コンストラクタ
//=============================================================================
CManager::CManager()
{
	
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
	//乱数の初期化
	srand((unsigned int)time(NULL));
	//レンダラーインスタンス生成
	m_pRenderer = new CRenderer;
	//サウンドインスタンス生成
	m_pSound = new CSound;

	// 初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		return -1;
	}
	//入力インスタンス生成
	m_pInputKeyboard = new CInputKeyboard;
	//入力初期化処理
	m_pInputKeyboard->Init(hInstance, hWnd);

	//テクスチャ読み込み
	TextureLoad();
	//サウンド初期化処理
	m_pSound->Init(hWnd);
	//モード設定
	SetMode(m_Mode);
	

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

	//キーボード入力更新
	m_pInputKeyboard->Update();

	//レンダラー更新処理
	m_pRenderer->Update();

	//画面遷移
	switch (m_Mode)
	{
	case MODE_TITLE://タイトル
		//エンターで次に進む
		if (pKey->GetkeyboardTrigger(DIK_RETURN))
		{	//チュートリアル画面に遷移
			SetMode(MODE_TUTORIAL);
		}
		break;
	case MODE_TUTORIAL://チュートリアル
		//エンターで次に進む
		if (pKey->GetkeyboardTrigger(DIK_RETURN))
		{
			//ゲームに遷移
			SetMode(MODE_GAME);
			
		}
		break;
	case MODE_GAME://ゲーム
		//エンターで次に進む
		if (CEnemy::GetEnemyDesu() >= 15)
		{
			//ゲームのクリア判定
			CResult::SetClear(false);
			//リザルトに遷移
			SetMode(MODE_RESULT);
		}
		

		break;
	case MODE_RESULT://リザルト
		//エンターで次に進む
		if (pKey->GetkeyboardTrigger(DIK_RETURN))
		{	//タイトルに遷移
			SetMode(MODE_TITLE);

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
	CPlayer::Load();
	CBullet::Load();
	CExplosion::Load();
	CEnemy::Load();
	CNumber::Load();
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
	CPlayer::Unload();
	CBullet::Unload();
	CExplosion::Unload();
	CEnemy::Unload();
	CNumber::Unload();
}

//=============================================================================
//モード設定関数
//=============================================================================
void CManager::SetMode(MODE mode)
{
	m_Mode = mode;
	//モードごとに設定
	switch (m_Mode)
	{
	case MODE_TITLE://タイトル
			//リザルトの終了処理
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		//タイトル生成
		m_pTitle = CTitle::Create();
		break;
	case MODE_TUTORIAL://チュートリアル
			//タイトルの終了処理
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		//チュートリアル生成
		m_pTutorial = CTutorial::Create();

		break;
	case MODE_GAME://ゲーム
			//チュートリアルの終了処理
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;
		}

		//2Dポリゴンの生成
		CBg::Create();
		//スコア生成
		CScore::Create();
		//敵生成
		CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (CEnemy::ENEMYTYPE)(rand() % (CEnemy::ENEMY_TYPE_MAX - 2)));
		//自機生成
		CPlayer::Create(D3DXVECTOR3(640, 600.0f, 0.0f));
		break;
	case MODE_RESULT://リザルト
		//敵出現数リセット
		CEnemy::SetNumEnemy(0);
		//敵討伐数リセット
		CEnemy::SetEnemyDesu(0);
		//すべて終了処理
		CScene::ReleaseAll();
		//リザルト生成
		m_pResult = CResult::Create();
		
		break;
	default:
		break;
	}
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
	pManager->Init( hInstance,  hWnd,  bWindow);
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
//プレイヤー所得関数
//=============================================================================
CPlayer * CManager::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
//音楽所得関数
//=============================================================================
CSound * CManager::GetSound(void)
{
	return m_pSound;
}