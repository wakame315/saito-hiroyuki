#include "life.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h" 

LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;
int CLife::m_life = 0;
CLife::CLife()
{
	m_life++;
	memset(m_apScene2d, 0, sizeof(m_apScene2d));
}

CLife::~CLife()
{
	m_life--;
}

HRESULT CLife::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	 //テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_NAME16,					// ファイルの名前
		&m_pTexture);									// 読み込むメモリー
	
	return S_OK;
}

void CLife::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

CLife * CLife::Create(void)
{
	CLife * pLife;
	pLife = new CLife;
	pLife->Init();


	return pLife;
}

HRESULT CLife::Init()
{
	for (int nCount = 0; nCount < PLAYER_MAX_LIFE; nCount++)
	{
		m_apScene2d[nCount] = new CScene2d; 
		m_apScene2d[nCount]->Init();
		m_apScene2d[nCount]->SetPosition(D3DXVECTOR3((1 + nCount) * LIFE_SIZE - LIFE_SIZE / 2, LIFE_SIZE / 2, 0.0f));
		m_apScene2d[nCount]->SetClo(D3DXCOLOR(NONE_CLO, NONE_CLO, NONE_CLO, NONE_CLO));
		m_apScene2d[nCount]->SetSize(LIFE_SIZE, LIFE_SIZE);
		m_apScene2d[nCount]->SetTexture();
		m_apScene2d[nCount]->BindTexture(m_pTexture);

	}

	return S_OK;
}

void CLife::Uninit(void)
{
	for (int nCount = 0; nCount < PLAYER_MAX_LIFE; nCount++)
	{
		m_apScene2d[nCount]->Uninit();
		m_apScene2d[nCount] = NULL;
	}

	Release();

}

void CLife::Update(void)
{

}

void CLife::Draw(void)
{

}

void CLife::lifeMode(int Damage)
{

}

