//=============================================================================
//
// 表示時間処理 [displaytime.cpp]
// Author :齋藤大行
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "displaytime.h"
#include "manager.h"
#include "input.h"
#include "inputkeyboard.h"
#include "renderer.h"
#include "main.h"

//=============================================================================
//静的メンバー変数
//=============================================================================
LPD3DXFONT CDisplaytime::m_pTimeFont = NULL;//フォントへのポインタ
LPD3DXFONT CDisplaytime::m_pMissFont = NULL;//フォントへのポインタ

//=============================================================================
//コンストラクタ
//=============================================================================
CDisplaytime::CDisplaytime() :CScene(4)
{
	m_dwGameStartTime = 0;
	m_dwTriggerGameTime = 0;
	m_dwTriggerTime = 0;
	m_dwGameTime = 0;
	m_dwGamePressStartTime = 0;
	m_bCntTimeUse = false;
	m_bDraw = false;
	m_bPressUse = false;
	m_bStartTime = false;
	m_nStop = 0;
}

//=============================================================================
//デストラクタ
//=============================================================================
CDisplaytime::~CDisplaytime()
{
	m_bCntTimeUse = false;
	m_bDraw = false;
}

//=============================================================================
//初期化処理関数
//=============================================================================
HRESULT CDisplaytime::Init(void)
{
	m_dwGameStartTime = 0;
	m_dwTriggerGameTime = 0;
	m_dwTriggerTime = 0;
	m_dwGameTime = 0;
	m_dwGamePressStartTime = 0;
	m_bCntTimeUse = false;
	m_bDraw = false;
	m_bPressUse = false;
	m_nStop = 0;

	return S_OK;
}

//=============================================================================
//終了処理関数
//=============================================================================
void CDisplaytime::Uninit(void)
{
	//オブジェクト破棄
	Release();
}

//=============================================================================
//更新処理関数
//=============================================================================
void CDisplaytime::Update(void)
{
	CInputKeyboard *pKey;
	pKey = CManager::GetInputKeyboard();
	

	switch (CManager::GetMode())
	{
	case CManager::MODE_TITLE:
		
		break;

	case CManager::MODE_TUTORIAL:

	
		break;

	case CManager::MODE_GAME:
		
		if (!m_bStartTime)
		{
			m_dwGameStartTime = timeGetTime();
			m_bStartTime = true;
		}

for (int nCntScene = 0; nCntScene < MAX_POLYGON*PRIORITY_MAX; nCntScene++)//シーンの所得
	{
		CScene *pScene = GetScene(nCntScene);
		CScene2d *pScene2d = (CScene2d*)pScene;//シーンのダブルポインタ
		if (pScene != NULL)
		{
			if (pScene->GetObjType() == TYPE_POLYGON)//オブジェクトがポリゴンの場合
			{
				if (((CPolygon*)pScene)->GetUse() == true && ((CPolygon*)pScene)->GetTexSignal() == CPolygon::TEX_SIGNAL_GO)//合図のポリゴンがオンの場合
				{
					if (m_bCntTimeUse == false)//合図が表示されてまだ結果時間をカウントしてないとき
					{
						if (m_nStop == 0)//一度だげ数値をとるため
						{
							m_dwTriggerTime = m_dwGameTime;//合図が表示された瞬間の時間を所得
							m_bCntTimeUse = true;//合図が表示されてからの時間をカウントを開始
							m_nStop = 1;//1を入れて読まれないようにする
						}
					}
					else if (m_bCntTimeUse == true)//結果時間のカウントをしているとき
					{
						if (pKey->GetkeyboardRelease(DIK_SPACE) == true)//SPACEキーを離した時
						{
							m_bPressUse = true;
							m_bCntTimeUse = false;//結果時間のカウントを止める
							m_bDraw = true;//結果時間の表示
						}
					}
				}
				else if (((CPolygon*)pScene)->GetTexSignal() == CPolygon::TEX_SIGNAL_GO && ((CPolygon*)pScene)->GetUse() == false)//合図のポリゴンがオフの場合
				{

					if (pKey->GetkeyboardRelease(DIK_SPACE) == true)//SPACEキーを離した時
					{
						m_bPressUse = true;
						m_bCntTimeUse = false;//結果時間のカウントを動かないようにする
						m_bDraw = true;//結果時間の表示
						for (int nCntScene = 0; nCntScene < MAX_POLYGON*PRIORITY_MAX; nCntScene++)//シーンの所得
						{
							CScene *pScene = GetScene(nCntScene);
							CScene2d *pScene2d = (CScene2d*)pScene;//シーンのダブルポインタ
							if (pScene != NULL)
							{
								if (pScene->GetObjType() == TYPE_POLYGON)//オブジェクトがポリゴンの場合
								{
									if (((CPolygon*)pScene)->GetTexSignal() == CPolygon::TEX_SIGNAL_MISS)//お手付きのポリゴンの場合
									{
										((CPolygon*)pScene)->SetbUse(true);//お手付きのポリゴンを表示する
									}
								}
							}
						}
					}
				}

			}
		}
	}

	if (pKey->GetkeyboardTrigger(DIK_SPACE) == true)
	{
   		m_dwGameStartTime = timeGetTime();
	}


	

	if (pKey->Getkeyboardpress(DIK_SPACE) == true)
	{
		m_dwGameTime = timeGetTime() - m_dwGameStartTime;
	}


	
	if (m_bCntTimeUse == true)
	{
		m_dwTriggerGameTime = m_dwGameTime - m_dwTriggerTime;
	}
		
	break;

	case CManager::MODE_RESULT:

		break;
	}
	
} 

//=============================================================================
//描画処理関数
//=============================================================================
void CDisplaytime::Draw(void)
{
	//時間表示
	//DrawTime(m_dwGameTime);

	if (m_bDraw == true)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON*PRIORITY_MAX; nCntScene++)
		{
			CScene *pScene = GetScene(nCntScene);
			CScene2d *pScene2d = (CScene2d*)pScene;
			if (pScene != NULL)
			{
				if (pScene->GetObjType() == TYPE_POLYGON)
				{
					if (((CPolygon*)pScene)->GetUse() == true && ((CPolygon*)pScene)->GetTexSignal() == CPolygon::TEX_SIGNAL_GO)
					{
						TriggerTime(m_dwTriggerGameTime);
					}
					else if (((CPolygon*)pScene)->GetUse() == false && ((CPolygon*)pScene)->GetTexSignal() == CPolygon::TEX_SIGNAL_GO)
					{
						DrawMiss();
					}
				}
			}
		}
	}
}

//=============================================================================
//経過時間描画用関数
//=============================================================================
void CDisplaytime::DrawTime(DWORD time)
{
	
		RECT rect = { SCREEN_WIDTH / 2.5, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		char str[256];

		sprintf(str, "経過時間:%.3f秒\n", (float)time / 1000.0f);

		// テキスト描画
		m_pTimeFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	
}

//=============================================================================
//結果時間描画関数
//=============================================================================
void CDisplaytime::TriggerTime(DWORD TriggerTime)
{
		RECT rect = { SCREEN_WIDTH / 2.5, 100, SCREEN_WIDTH, SCREEN_HEIGHT };
		char str[256];

		sprintf(str, "結果時間:%.3f秒\n", (float)TriggerTime / 1000.0f);

		// テキスト描画
		m_pTimeFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0, 0, 0));
}

//=============================================================================
//お手付き描画関数
//=============================================================================
void CDisplaytime::DrawMiss(void)
{
	RECT rect = { SCREEN_WIDTH / 2.5, 100, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	sprintf(str, "結果:お手付き");

	// テキスト描画
	m_pMissFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0, 0, 0));
}

//=============================================================================
//経過時間所得関数
//=============================================================================
DWORD CDisplaytime::GetTime(void)
{
	return m_dwGameTime;
}

//=============================================================================
//結果時間所得関数
//=============================================================================
DWORD CDisplaytime::GetTriggerTime(void)
{
	return m_dwTriggerGameTime;
}

//=============================================================================
//フォント生成処理関数
//=============================================================================
HRESULT CDisplaytime::FontCreate(void)
{

	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 時間情報表示用フォントの生成
	D3DXCreateFont(pDevice, 50, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pTimeFont);

	// お手付き情報表示用フォントの生成
	D3DXCreateFont(pDevice, 50, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pMissFont);
	
	return S_OK;
}

//=============================================================================
//フォント終了処理関数
//=============================================================================
void CDisplaytime::FontUninit(void)
{
	if (m_pTimeFont != NULL)
	{
		m_pTimeFont->Release();
		m_pTimeFont = NULL;
	}
	if (m_pMissFont != NULL)
	{
		m_pMissFont->Release();
		m_pMissFont = NULL;
	}
}

//=============================================================================
//生成処理関数
//=============================================================================
CDisplaytime * CDisplaytime::Create()
{
	CDisplaytime * pDisplaytime;
	pDisplaytime = new CDisplaytime;
	pDisplaytime->Init();
	pDisplaytime->SetObjType(TYPE_DISPLAYTIME);
	return pDisplaytime;
}

