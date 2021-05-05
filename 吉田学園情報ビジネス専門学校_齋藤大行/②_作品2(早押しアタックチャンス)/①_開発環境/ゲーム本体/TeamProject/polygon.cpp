#include "polygon.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "inputkeyboard.h"
#include "displaytime.h"
#include "main.h"
#include "sound.h"

LPDIRECT3DTEXTURE9 CPolygon::m_pTexture[MAX_SIGNAL] = {};

CPolygon::CPolygon():CScene2d(2)
{
	m_tSignal = TEX_SIGNAL_NONE;
	m_buse = false;
	m_nUseNum = 0;
	m_nMultiplication = 0;
	m_nOnePlay = 0;
}

CPolygon::~CPolygon()
{
}

HRESULT CPolygon::Load(void)
{
	// テクスチャの生成
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),	// デバイスへのポインタ
		TEXTURE_NAME1,					// ファイルの名前
		&m_pTexture[0]);					// 読み込むメモリー

	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),	// デバイスへのポインタ
		TEXTURE_NAME2,					// ファイルの名前
		&m_pTexture[1]);					// 読み込むメモリー


	return S_OK;
}

void CPolygon::Unload(void)
{
	for (int nCount = 0; nCount < MAX_SIGNAL; nCount++)
	{
		//テクスチャの開放
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

HRESULT CPolygon::Init(TEX_SIGNAL signal)
{
	CScene2d::Init();
	CScene2d::BindTexture(m_pTexture[signal - 1]);
	SetTexSignal(signal);
	GetRandom();
	m_buse = false;

	return S_OK;
}

void CPolygon::Uninit(void)
{
	CScene2d::Uninit();
}

void CPolygon::Update(void)
{
	CInputKeyboard *pKey;
	pKey = CManager::GetInputKeyboard();
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	SetTexture();
	pos = GetPosition();
	rot = GetRot();
	CSound *pSound = CManager::GetSound();


	for (int nCntScene = 0; nCntScene < MAX_POLYGON*PRIORITY_MAX; nCntScene++)
	{
		CScene *pScene = GetScene(nCntScene);
		CScene2d *pScene2d = (CScene2d*)pScene;
		if (pScene != NULL)
		{
			if (pScene->GetObjType() == TYPE_DISPLAYTIME)
			{
				if (((CDisplaytime*)pScene)->GetTime() >= m_nUseNum)
				{	
					if (m_tSignal == TEX_SIGNAL_GO)
					{
						if (m_nOnePlay == 0)
						{
							pSound->Play(CSound::SE_GO);
							m_nOnePlay = 1;
						}
						m_buse = true;
					}
					
					
				}
			}
		}
	}

	SetRot(rot);

	//頂点情報を設定

	CScene2d::Update();

}

void CPolygon::Draw(void)
{
	if (m_buse == true)
	{
		CScene2d::Draw();
	}
}

void CPolygon::SetTexSignal(TEX_SIGNAL Type)
{
	m_tSignal = Type;
}

bool CPolygon::SetbUse(bool bUse)
{
	m_buse = bUse;

	return m_buse;
}

CPolygon * CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEX_SIGNAL signal)
{
	CPolygon * pPolygon;
	pPolygon = new CPolygon;
	pPolygon->SetPosition(D3DXVECTOR3(pos.x, pos.y,0.0f));
	pPolygon->SetSize(size.x, size.y);
	pPolygon->SetClo(D3DXCOLOR(255, 255, 255, 255));
	pPolygon->SetObjType(TYPE_POLYGON);
	pPolygon->Init(signal);
	return pPolygon;
}

bool CPolygon::GetUse(void)
{
	return m_buse;
}

int CPolygon::GetRandom(void)
{
	int nRand = 0;
	int nRand2 = 0;
	static int flag = 0;

	if (flag == 0) {
		srand((unsigned int)time(NULL));
		flag = 1;
	}

	nRand = (int)rand() % 110 + 1001;
	nRand2 = (int)rand() % 6 + 5;
	m_nUseNum = nRand *nRand2;

	return m_nUseNum;
}