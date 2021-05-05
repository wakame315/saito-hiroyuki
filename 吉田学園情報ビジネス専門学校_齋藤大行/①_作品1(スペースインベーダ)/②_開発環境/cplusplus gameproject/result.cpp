#include "result.h"
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"

LPDIRECT3DTEXTURE9 CResult::m_pTexture[RESULT_TEXTURE] = {};
bool CResult::m_bClear = false;
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
		TEXTURE_NAME15,								// ファイルの名前
		&m_pTexture[0]);

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_NAME16,								// ファイルの名前
		&m_pTexture[1]);

	return S_OK;
}

void CResult::Unload(void)
{
	for (int nCount = 0; nCount < RESULT_TEXTURE; nCount++)
	{
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

CResult * CResult::Create(void)
{
	CResult *pResult;
	pResult = new CResult;
	pResult->Init();

	return pResult;
}

void CResult::SetClear(bool Clear)
{
	m_bClear = Clear;
}

HRESULT CResult::Init(void)
{
	m_apScene2d = new CScene2d;
	m_apScene2d->Init();
	m_apScene2d->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_apScene2d->SetClo(D3DXCOLOR(NONE_CLO, NONE_CLO, NONE_CLO, NONE_CLO));
	m_apScene2d->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_apScene2d->SetObjType(CScene::TYPE_RESULT);
	m_apScene2d->SetTexture();
	
	if (m_bClear)
	{
		m_apScene2d->BindTexture(m_pTexture[0]);
	}
	else
	{
		m_apScene2d->BindTexture(m_pTexture[1]);
	}

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
