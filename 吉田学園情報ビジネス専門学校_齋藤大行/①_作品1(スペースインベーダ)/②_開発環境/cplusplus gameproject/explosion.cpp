//=============================================================================
//
// 爆発処理 [explosion.cpp]
// Author :齋藤大行
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "explosion.h"
#include "scene2d.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "main.h"
#include "bullet.h"

//=============================================================================
//静的メンバー変数
//=============================================================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture[MAX_EXPLOSION_TEXTURE] = {};

//=============================================================================
//コンストラクタ
//=============================================================================
CExplosion::CExplosion():CScene2d(3)
{
	m_nCounterAnim = 0;//アニメーションカウント
	m_nPatternAnim = 0;//アニメーションパターン
}

//=============================================================================
//デストラクタ
//=============================================================================
CExplosion::~CExplosion()
{
}

//=============================================================================
//テクスチャロード関数
//=============================================================================
HRESULT CExplosion::Load(void)
{
	// テクスチャの生成
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),			// デバイスへのポインタ
	TEXTURE_NAME3,															// ファイルの名前
	&m_pTexture[EXPLOSION_BULLET]);														// 読み込むメモリー

																			// テクスチャの生成
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),			// デバイスへのポインタ
	TEXTURE_NAME5,															// ファイルの名前
	&m_pTexture[EXPLOSION_CHARACTER]);

	return S_OK;
}

//=============================================================================
//テクスチャアンロード関数
//=============================================================================
void CExplosion::Unload(void)
{
	for (int nCount = 0; nCount < MAX_EXPLOSION_TEXTURE; nCount++)
	{
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
//生成処理関数
//=============================================================================
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, D3DXCOLOR clo, int nSize, EXPLOSION type)
{
	CExplosion * pExplosion;				   //ポインタ
	pExplosion = new CExplosion;			   //インスタンス生成
	pExplosion->Init(type);					   //初期化処理
	pExplosion->SetClo(clo);				   //色設定
	pExplosion->SetPosition(pos);			   //位置設定
	pExplosion->SetSize(nSize, nSize);		   //サイズ設定
											   
	return pExplosion;
}

//=============================================================================
//初期化処理関数
//=============================================================================
HRESULT CExplosion::Init(EXPLOSION type)
{
	CScene2d::Init();
	CScene2d::BindTexture(m_pTexture[type]);
	
	return S_OK;
}

//=============================================================================
//終了処理関数
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//更新処理関数
//=============================================================================
void CExplosion::Update(void)
{
	D3DXVECTOR3 pos;			 //位置
	D3DXVECTOR3 move;			 //移動量
	EXPLOSION type;				 //タイプ

	pos = GetPosition();		 //位置所得
	move = GetMove();			 //移動量所得
								 
	//アニメーションのカウント
		m_nCounterAnim++;
			//カウントが4になったら
		if (m_nCounterAnim >= 4)
		{
			m_nCounterAnim = 0;//カウンター初期値に戻す
			m_nPatternAnim++;//パターンを帰る


			SetAnim(m_nPatternAnim);//アニメーションの設定
			

			SetPosition(pos);//位置の設定
		

			CScene2d::Update(); //Scene2dを読み込む
	
			//パターンが8になったら
			if (m_nPatternAnim >= 8)
			{	//ゼロに戻す
				m_nPatternAnim = 0;
				//初期化処理
				Uninit();
			}

		}
}

//=============================================================================
//描画処理関数
//=============================================================================
void CExplosion::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
//^アニメーションのパターン所得
//=============================================================================
int CExplosion::GetPatternAnim(void)
{
	return m_nPatternAnim;
}
