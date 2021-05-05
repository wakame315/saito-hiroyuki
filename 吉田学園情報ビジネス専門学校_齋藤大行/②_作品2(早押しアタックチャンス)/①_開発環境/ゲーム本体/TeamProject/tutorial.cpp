#include "tutorial.h"

LPDIRECT3DTEXTURE9 CTutorial::m_pTexture = NULL;

CTutorial::CTutorial()
{
}

CTutorial::~CTutorial()
{
}

HRESULT CTutorial::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_NAME8,								// ファイルの名前
		&m_pTexture);
	return S_OK;
}

void CTutorial::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

CTutorial * CTutorial::Create(void)
{
	CTutorial *pTutorial;
	pTutorial = new CTutorial;
	pTutorial->Init();
	return pTutorial;
}

HRESULT CTutorial::Init(void)
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

void CTutorial::Uninit(void)
{
	if (m_apScene2d != NULL)
	{
		m_apScene2d->Uninit();
		m_apScene2d = NULL;
	}
}

void CTutorial::Update(void)
{
}

void CTutorial::Draw(void)
{
	m_apScene2d->Draw();
}
