//=============================================================================
//
// ポリゴン処理 [polygon.cpp]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "polygon.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "inputkeyboard.h"
#include "displaytime.h"
#include "main.h"
#include "sound.h"


//=============================================================================
//静的メンバー変数
//=============================================================================
LPDIRECT3DTEXTURE9 CPolygon::m_pTexture[MAX_SIGNAL] = {};

//=============================================================================
//コンストラクタ
//=============================================================================
CPolygon::CPolygon():CScene2d(2)
{
	m_tSignal = TEX_SIGNAL_NONE;//たいぷの初期化
	m_buse = false;//フラグの初期化
	m_nUseNum = 0;//合図の数値
	m_nOnePlay = 0;//一度だけのフラグ
}

//=============================================================================
//デストラクタ
//=============================================================================
CPolygon::~CPolygon()
{
}

//=============================================================================
//テクスチャロード
//=============================================================================
HRESULT CPolygon::Load(void)
{
	// テクスチャの生成
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),	// デバイスへのポインタ
		TEXTURE_NAME1,					// ファイルの名前
		&m_pTexture[0]);					// 読み込むメモリー

	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),	// デバイスへのポインタ
		TEXTURE_NAME2,					// ファイルの名前
		&m_pTexture[1]);					// 読み込むメモリー


	return S_OK;
}

//=============================================================================
//テクスチャアンロード
//=============================================================================
void CPolygon::Unload(void)
{
	for (int nCount = 0; nCount < MAX_SIGNAL; nCount++)
	{
		//テクスチャの開放
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
//初期化処理関数
//=============================================================================
HRESULT CPolygon::Init(TEX_SIGNAL signal)
{
	CScene2d::Init();
	CScene2d::BindTexture(m_pTexture[signal - 1]);
	SetTexSignal(signal);
	GetRandom();
	m_buse = false;

	return S_OK;
}

//=============================================================================
//終了処理関数
//=============================================================================
void CPolygon::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//更新処理関数
//=============================================================================
void CPolygon::Update(void)
{
	//キーボードのポインタ
	CInputKeyboard *pKey;
	pKey = CManager::GetInputKeyboard();

	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;

	//テクスチャ設定
	SetTexture();
	//場所を所得
	pos = GetPosition();
	//角度を所得
	rot = GetRot();
	//サウンド所得
	CSound *pSound = CManager::GetSound();

	//シーンを1つずつ見ていく
	for (int nCntScene = 0; nCntScene < MAX_POLYGON*PRIORITY_MAX; nCntScene++)
	{
		CScene *pScene = GetScene(nCntScene);
		CScene2d *pScene2d = (CScene2d*)pScene;
		//NULLチェック
		if (pScene != NULL)
		{	//タイプがTYPE_DISPLAYTIMEだった場合
			if (pScene->GetObjType() == TYPE_DISPLAYTIME)
			{
				//経過時間がランダムの設定時間を超えたら
				if (((CDisplaytime*)pScene)->GetTime() >= m_nUseNum)
				{	//合図をだす
					if (m_tSignal == TEX_SIGNAL_GO)
					{	//フラグが0なら
						if (m_nOnePlay == 0)
						{	//効果音を再生
							pSound->Play(CSound::SE_GO);
							//フラグを1にする
							m_nOnePlay = 1;
						}
						//合図のしようフラグをtrueにする
						m_buse = true;
					}
					
					
				}
			}
		}
	}
	//角度の設定
	SetRot(rot);

	//Scene2dの更新を読み込む
	CScene2d::Update();

}

//=============================================================================
//描画処理
//=============================================================================
void CPolygon::Draw(void)
{
	if (m_buse == true)
	{
		CScene2d::Draw();
	}
}

//=============================================================================
//タイプごとのテクスチャ設定
//=============================================================================
void CPolygon::SetTexSignal(TEX_SIGNAL Type)
{
	m_tSignal = Type;
}

//=============================================================================
//合図の使用フラグの設定関数
//=============================================================================
bool CPolygon::SetbUse(bool bUse)
{
	m_buse = bUse;

	return m_buse;
}

//=============================================================================
//生成処理関数
//=============================================================================
CPolygon * CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEX_SIGNAL signal)
{
	CPolygon * pPolygon;
	pPolygon = new CPolygon;
	pPolygon->SetPosition(D3DXVECTOR3(pos.x, pos.y,0.0f));
	pPolygon->SetSize(size.x, size.y);
	pPolygon->SetClo(D3DXCOLOR(255, 255, 255, 255));
	pPolygon->SetObjType(TYPE_POLYGON);
	pPolygon->Init(signal);
	return pPolygon;
}

//=============================================================================
//合図の使用フラグの設定関数
//=============================================================================
bool CPolygon::GetUse(void)
{
	return m_buse;
}

//=============================================================================
//乱数所得関数
//=============================================================================
int CPolygon::GetRandom(void)
{
	int nRand = 0;
	int nRand2 = 0;
	static int flag = 0;

	if (flag == 0) {
		srand((unsigned int)time(NULL));
		flag = 1;
	}

	nRand = (int)rand() % 110 + 1001;
	nRand2 = (int)rand() % 6 + 5;
	m_nUseNum = nRand *nRand2;

	return m_nUseNum;
}