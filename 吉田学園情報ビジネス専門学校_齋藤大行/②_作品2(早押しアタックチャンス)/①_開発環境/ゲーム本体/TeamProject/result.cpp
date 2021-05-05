#include "result.h"
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"

LPDIRECT3DTEXTURE9 CResult::m_pTexture = NULL;

CResult::CResult(int nPriority)
{
	m_apScene2d = NULL;

}

CResult::~CResult()
{
}

HRESULT CResult::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_NAME3,								// ファイルの名前
		&m_pTexture);
	return S_OK;
}

void CResult::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

CResult * CResult::Create(void)
{
	CResult *pResult;
	pResult = new CResult;
	pResult->Init();
	return pResult;
}

HRESULT CResult::Init(void)
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

void CResult::Uninit(void)
{

	m_apScene2d->Uninit();
	m_apScene2d = NULL;
}

void CResult::Update(void)
{
}

void CResult::Draw(void)
{
	m_apScene2d->Draw();
}
