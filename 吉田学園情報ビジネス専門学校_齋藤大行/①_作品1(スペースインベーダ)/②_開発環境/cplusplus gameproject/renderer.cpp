#include"renderer.h"
#include"scene.h"
#include "manager.h"
#include "number.h"

CRenderer::CRenderer()
{ 
	m_pD3D = 0;
	m_pD3DDevice = 0;
	m_pFont = 0;
	
}

CRenderer::~CRenderer()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;							// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;				// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;					// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;						// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
																	// インターバル

	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// デバイスの生成
																// ディスプレイアダプタを表すためのデバイスを作成
																// 描画と頂点処理をハードウェアで行なう
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// 生成失敗
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

#ifdef _DEBUG
	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
#endif

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CRenderer::Uninit(void)
{
#ifdef _DEBUG
	// デバッグ情報表示用フォントの破棄
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
#endif

	// デバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void CRenderer::Update(void)
{
	CScene::UpdateAll();
}
//=============================================================================
// 描画処理
//=============================================================================
void CRenderer::Draw(void)
{

	// バックバッファ＆Ｚバッファのクリア
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 5), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{

		CScene::DrawAll();

#ifdef _DEBUG
		// FPS表示
		DrawFPS();
#endif
		// Direct3Dによる描画の終了
		m_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

#ifndef Si

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CRenderer::InitPolygon(void)
{

	// ポリゴンの位置を設定
	m_posPolygon = D3DXVECTOR3(640, 360, 0);
	// テクスチャの生成
	D3DXCreateTextureFromFile(m_pD3DDevice,				// デバイスへのポインタ
		TEXTURE_NAME,					// ファイルの名前
		&m_pTexture);									// 読み込むメモリー

														// 頂点バッファの生成
	if (FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
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

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	// 頂点情報を設定
	pVtx[0].Pos = D3DXVECTOR3(m_posPolygon.x + (-POLYGON_SIZE_Y / 2), m_posPolygon.y + (-POLYGON_SIZE_Y / 2), 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(m_posPolygon.x + (POLYGON_SIZE_X / 2) , m_posPolygon.y + (-POLYGON_SIZE_Y / 2), 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(m_posPolygon.x + (-POLYGON_SIZE_X / 2), m_posPolygon.y + (POLYGON_SIZE_Y / 2), 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(m_posPolygon.x + (POLYGON_SIZE_X / 2) , m_posPolygon.y + (POLYGON_SIZE_Y / 2), 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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
// ポリゴンの終了処理
//=============================================================================
void CRenderer::UninitPolygon(void)
{
	//テクスチャの開放
	if (m_pTexture != NULL)
	{	
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	//頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{	
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CRenderer::UpdatePolygon(void)
{

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	static float fradian = 0.0f;
	static float fradius = 0.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fradius = sqrtf(((TEXTURE_WIDTH / 2)*(TEXTURE_WIDTH / 2)) + ((TEXTURE_HEIGHT / 2)*(TEXTURE_HEIGHT / 2)));
	fradian = atan2f((TEXTURE_HEIGHT / 2), (TEXTURE_WIDTH / 2));


	m_rot.z += D3DX_PI * 0.01f;
	if (m_rot.z >= D3DX_PI)
	{	
		m_rot.z -= D3DX_PI * 2.0f;
	}

	//頂点情報を設定
	VERTEX_2D *pVtx;


	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].Pos = D3DXVECTOR3(m_posPolygon.x - (cosf(fradian - m_rot.z) * fradius), m_posPolygon.y - (sinf(fradian - m_rot.z) * fradius), 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(m_posPolygon.x + (cosf(fradian + m_rot.z) * fradius), m_posPolygon.y - (sinf(fradian + m_rot.z) * fradius), 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(m_posPolygon.x - (cosf(fradian + m_rot.z) * fradius), m_posPolygon.y + (sinf(fradian + m_rot.z) * fradius), 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(m_posPolygon.x + (cosf(fradian - m_rot.z) * fradius), m_posPolygon.y + (sinf(fradian - m_rot.z) * fradius), 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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


}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CRenderer::DrawPolygon(void)
{

	//頂点バッファをデバイスのデータストリームにバインド
	m_pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	m_pD3DDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	m_pD3DDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

#endif // !SU

#ifdef _DEBUG
//=============================================================================
// FPS表示
//=============================================================================
void CRenderer::DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	wsprintf(str, "FPS:%d\n", GetFPS());

	// テキスト描画
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif


