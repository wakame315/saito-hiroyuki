//=============================================================================
//
// シーン処理 [scene.cpp]
// Author : 齋藤大行
//
//=============================================================================

#include "scene.h"


//=============================================================================
//静的メンバー変数
//=============================================================================
CScene * CScene::m_apScene[PRIORITY_MAX][MAX_POLYGON] = {};
int CScene::m_nNumAll = 0;

//=============================================================================
//コンストラクタ
//=============================================================================
CScene::CScene(int nPriority)
{
	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_nPriority = nPriority;
			m_apScene[nPriority][nCntScene] = this;
			m_objType = TYPE_NONE;
			m_nID = nCntScene;
			m_nNumAll++;
			break;
		}
	}
}

//=============================================================================
//デストラクタ
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
//全更新関数
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				// ポリゴンの更新処理
				m_apScene[nCntPriority][nCntScene]->Update();
			}
		}
	}
}

//=============================================================================
//全描画処理関数
//=============================================================================
void CScene::DrawAll(void)
{

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				// ポリゴンの更新処理
				m_apScene[nCntPriority][nCntScene]->Draw();
			}
		}
	}
}
//=============================================================================
//全終了処理関数
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				m_apScene[nCntPriority][nCntScene]->Uninit();
			}
		}
	}
}

//=============================================================================
//終了処理関数
//=============================================================================
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}

//=============================================================================
//オブジェクト設定関数
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//=============================================================================
//シーン所得関数
//=============================================================================
CScene * CScene::GetScene(int nCnt)
{
	return m_apScene[0][nCnt];
}

