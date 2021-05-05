#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "inputkeyboard.h"

CScene2d::CScene2d(int nPriority) : CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_Size_x = 0;
	m_Size_y = 0;
	m_pTexture = 0;
	m_pVtxBuff = 0;
	m_bDraw = false;
}

CScene2d::~CScene2d()
{
}

HRESULT CScene2d::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	
	

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * MAX_POLYGON,	// 頂点データ用に確保するバッファサイズ(バイト単位)
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
	pVtx[0].Pos = D3DXVECTOR3(m_pos.x + (-POLYGON_SIZE_Y / 2), m_pos.y + (-POLYGON_SIZE_Y / 2), 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(m_pos.x + (POLYGON_SIZE_X / 2), m_pos.y + (-POLYGON_SIZE_Y / 2), 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(m_pos.x + (-POLYGON_SIZE_X / 2), m_pos.y + (POLYGON_SIZE_Y / 2), 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(m_pos.x + (POLYGON_SIZE_X / 2), m_pos.y + (POLYGON_SIZE_Y / 2), 0.0f);

	//rhwnの設定（値は1.0で固定）
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点のカラー(0〜255の範囲で設定)
	pVtx[0].clo = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].clo = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].clo = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].clo = D3DCOLOR_RGBA(255, 255, 255, 255);

	m_pVtxBuff->Unlock();


	return S_OK;
}

void CScene2d::Uninit(void)
{

	//頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//オブジェクト破棄
	Release();
}

void CScene2d::Update(void)
{
	//CInputKeyboard *pKey;
	//pKey = CManager::GetInputKeyboard();
	//

	//static float fradian = 0.0f;
	//static float fradius = 0.0f;
	//fradius = sqrtf((float)(((TEXTURE_WIDTH / 2)*(TEXTURE_WIDTH / 2)) + ((TEXTURE_HEIGHT / 2)*(TEXTURE_HEIGHT / 2))));
	//fradian = atan2f((TEXTURE_HEIGHT / 2), (TEXTURE_WIDTH / 2));

	//if (pKey->Getkeyboardpress(DIK_W) == true)
	//{

	//	m_rot.z += D3DX_PI * 0.01f;
	//	if(m_rot.z >= D3DX_PI)
	//		{
	//			m_rot.z -= D3DX_PI * 2.0f;
	//	}

	//	m_pos.x += 1.0f;
	//}
	//
	//


	//頂点情報を設定
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].Pos = D3DXVECTOR3(m_pos.x - (m_Size_x / 2), m_pos.y - (m_Size_y / 2), 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(m_pos.x + (m_Size_x / 2), m_pos.y - (m_Size_y / 2), 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(m_pos.x - (m_Size_x / 2), m_pos.y + (m_Size_y / 2), 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(m_pos.x + (m_Size_x / 2), m_pos.y + (m_Size_y / 2), 0.0f);

	//頂点のカラー(0〜255の範囲で設定)
	pVtx[0].clo = D3DCOLOR_RGBA(m_clo_r, m_clo_g, m_clo_b, m_clo_a);
	pVtx[1].clo = D3DCOLOR_RGBA(m_clo_r, m_clo_g, m_clo_b, m_clo_a);
	pVtx[2].clo = D3DCOLOR_RGBA(m_clo_r, m_clo_g, m_clo_b, m_clo_a);
	pVtx[3].clo = D3DCOLOR_RGBA(m_clo_r, m_clo_g, m_clo_b, m_clo_a);

	m_pVtxBuff->Unlock();
}

void CScene2d::Draw(void)
{
	if (m_bDraw == false)
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
}



void CScene2d::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

D3DXVECTOR3 CScene2d::GetPosition(void)
{
	return m_pos;
}

void CScene2d::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

D3DXVECTOR3 CScene2d::GetMove(void)
{
	return m_move;
}

void CScene2d::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

D3DXVECTOR3 CScene2d::GetRot(void)
{
	return m_rot;
}

void CScene2d::SetSize(int Size_x, int Size_y)
{
	m_Size_x = Size_x;
	m_Size_y = Size_y;
}

void CScene2d::SetAnim(int nPatternAnim)
{
	m_nPatternAnim = nPatternAnim;

	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.125f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.125f + 0.125f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.125f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.125f + 0.125f, 1.0f);//テクスチャ座標を更新

	m_pVtxBuff->Unlock();
}

D3DXCOLOR CScene2d::GetClo(void)
{
	return m_clo;
}

void CScene2d::SetClo(D3DXCOLOR nClo)
{
	m_clo_r = nClo.r;
	m_clo_g = nClo.g;
	m_clo_b = nClo.b;
	m_clo_a = nClo.a;
}

void CScene2d::SetTexture(void)
{
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

}

bool CScene2d::GetDraw(void)
{
	return m_bDraw;
}

void CScene2d::SetDraw(bool DrawUse)
{
	m_bDraw = DrawUse;
}



CScene2d *CScene2d::Create()
{
	CScene2d * pScene2d;
	pScene2d = new CScene2d;
	pScene2d->Init();
	return pScene2d;
}

void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

