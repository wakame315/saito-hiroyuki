#include "title.h"
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"

LPDIRECT3DTEXTURE9 CTitle::m_pTexture = NULL;

CTitle::CTitle()
{
	m_apScene2d = NULL;
}

CTitle::~CTitle()
{
}

HRESULT CTitle::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_NAME6,								// ファイルの名前
		&m_pTexture);
	return S_OK;
}

void CTitle::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

CTitle * CTitle::Create(void)
{
	CTitle *pTitle;
	pTitle = new CTitle;
	pTitle->Init();
	return pTitle;
}

HRESULT CTitle::Init(void)
{
	m_apScene2d = new CScene2d;
	m_apScene2d->Init();
	m_apScene2d->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_apScene2d->SetClo(D3DXCOLOR(NONE_CLO, NONE_CLO, NONE_CLO, NONE_CLO));
	m_apScene2d->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_apScene2d->SetTexture();
	m_apScene2d->BindTexture(m_pTexture);

	return S_OK;
}

void CTitle::Uninit(void)
{
	if (m_apScene2d != NULL)
	{
		m_apScene2d->Uninit();
		m_apScene2d = NULL;
	}

}

void CTitle::Update(void)
{
}

void CTitle::Draw(void)
{
	m_apScene2d->Draw();
}
