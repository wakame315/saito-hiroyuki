//=============================================================================
//
// 数字の処理 [number.cpp]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h" 

//=============================================================================
//静的メンバー変数
//=============================================================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//=============================================================================
//コンストラクタ
//=============================================================================
CNumber::CNumber()
{
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_nNumber = 0;
}

//=============================================================================
//デストラクタ
//=============================================================================
CNumber::~CNumber()
{

}

//=============================================================================
//テクスチャロード関数
//=============================================================================
HRESULT CNumber::Load(void)
{
	// テクスチャの生成
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),			// デバイスへのポインタ
		TEXTURE_NAME13,					// ファイルの名前
		&m_pTexture);		// 読み込むメモリー

	return S_OK;
}

//=============================================================================
//テクスチャアンロード関数
//=============================================================================
void CNumber::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//生成処理関数
//=============================================================================
CNumber * CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNum)
{
	CNumber * pNumber;			//ポインタ
	pNumber = new CNumber;		//インスタンス生成
	pNumber->Init();			//初期化処理
	pNumber->SetPosition(pos);	//位置設定
	pNumber->SetSize(size);		//サイズ設定
	pNumber->SetNumber(nNum);	//数字設定
	
	return pNumber;
}

//=============================================================================
//初期化処理関数
//=============================================================================
HRESULT CNumber::Init()
{
	m_nNumber = 0;

	// 頂点バッファの生成
	if (FAILED(CManager::GetRenderer()->GetDevice()->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * MAX_SCENE,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,				// 頂点バッファへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}
	

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].Pos = D3DXVECTOR3(m_pos.x + (-m_size.x / 2), m_pos.y + (-m_size.y / 2), 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(m_pos.x + ( m_size.x / 2), m_pos.y + (-m_size.y / 2), 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(m_pos.x + (-m_size.x / 2), m_pos.y + ( m_size.y / 2), 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(m_pos.x + ( m_size.x / 2), m_pos.y + ( m_size.y / 2), 0.0f);

	//rhwnの設定（値は1.0で固定）
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点のカラー(0～255の範囲で設定)
	pVtx[0].clo = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].clo = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].clo = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].clo = D3DCOLOR_RGBA(255, 255, 255, 255);

	m_pVtxBuff->Unlock();


	return S_OK;
}

//=============================================================================
//終了処理関数
//=============================================================================
void CNumber::Uninit(void)
{
	//頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
//更新処理関数
//=============================================================================
void CNumber::Update(void)
{
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].Pos = D3DXVECTOR3(m_pos.x + (-m_size.x / 2), m_pos.y + (-m_size.y / 2), 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (-m_size.y / 2), 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(m_pos.x + (-m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	pVtx[0].tex = D3DXVECTOR2(m_nNumber * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_nNumber * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_nNumber * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_nNumber * 0.1f + 0.1f, 1.0f);//テクスチャ座標を更新

	m_pVtxBuff->Unlock();
}

//=============================================================================
//描画処理関数
//=============================================================================
void CNumber::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
//位置設定
//=============================================================================
void CNumber::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
//サイズ設定
//=============================================================================
void CNumber::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
//数字設定
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	m_nNumber = nNumber;
}
