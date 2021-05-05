#include "bg.h"
#include "manager.h"
#include "renderer.h"

LPDIRECT3DTEXTURE9 CBg::m_pTexture[MAX_TEXTURE] = {};

CBg::CBg() :CScene(0)
{
	memset(m_apScene2d, 0, sizeof(m_apScene2d));
}


CBg::~CBg()
{
}

HRESULT CBg::Load(void)
{

	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_NAME4,					// ファイルの名前
		&m_pTexture[0]);									// 読み込むメモリー

															// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_NAME5,					// ファイルの名前
		&m_pTexture[1]);									// 読み込むメモリー

															// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_NAME6,					// ファイルの名前
		&m_pTexture[2]);									// 読み込むメモリー

															// テクスチャの生成
	//D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
	//	TEXTURE_NAME1,					// ファイルの名前
	//	&m_pTexture[3]);									// 読み込むメモリー

	//														// テクスチャの生成
	//D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
	//	TEXTURE_NAME1,					// ファイルの名前
	//	&m_pTexture[4]);									// 読み込むメモリー


	return S_OK;
}

void CBg::Unload(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		if (m_pTexture != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}

}

CBg * CBg::Create(void)
{
	CBg * pBg;
	pBg = new CBg;
   	pBg->Init();
	pBg->SetObjType(TYPE_BG);
	
	return pBg;
}

HRESULT CBg::Init(void)
{	
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		m_apScene2d[nCount] = new CScene2d;
		m_apScene2d[nCount]->Init();
		m_apScene2d[nCount]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,0.0f));
		m_apScene2d[nCount]->SetClo(D3DXCOLOR(NONE_CLO, NONE_CLO, NONE_CLO, NONE_CLO));
		m_apScene2d[nCount]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		m_apScene2d[nCount]->SetTexture();
		m_apScene2d[nCount]->BindTexture(m_pTexture[nCount]);	

	}
	
	return S_OK;
}

void CBg::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		m_apScene2d[nCount]->Uninit();
		m_apScene2d[nCount] = NULL;
	}


	Release();
}

void CBg::Update(void)
{

}

void CBg::Draw(void)
{

}
