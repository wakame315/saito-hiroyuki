#include "scene.h"

CScene * CScene::m_apScene[PRIORITY_MAX][MAX_SCENE] = {};
int CScene::m_nNumAll = 0;

CScene::CScene(int nPriority)
 {
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
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

CScene::~CScene()
{
}

void CScene::UpdateAll(void)
{
	for (int nCntPriority= 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				// ポリゴンの更新処理
				m_apScene[nCntPriority][nCntScene]->Update();
			}
		}
	}
}

void CScene::DrawAll(void)
{

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				// ポリゴンの更新処理
				m_apScene[nCntPriority][nCntScene]->Draw();
			}
		}
	}
}

void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				m_apScene[nCntPriority][nCntScene]->Uninit();
			}
		}
	}
}


void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;
		delete m_apScene[m_nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}

void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

CScene * CScene::GetScene(int nCnt )
{
	return m_apScene[0][nCnt];
}

