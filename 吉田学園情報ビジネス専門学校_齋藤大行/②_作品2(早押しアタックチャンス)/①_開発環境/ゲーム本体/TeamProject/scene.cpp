//=============================================================================
//
// �V�[������ [scene.cpp]
// Author : �V����s
//
//=============================================================================

#include "scene.h"


//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
CScene * CScene::m_apScene[PRIORITY_MAX][MAX_POLYGON] = {};
int CScene::m_nNumAll = 0;

//=============================================================================
//�R���X�g���N�^
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
//�f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
//�S�X�V�֐�
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				// �|���S���̍X�V����
				m_apScene[nCntPriority][nCntScene]->Update();
			}
		}
	}
}

//=============================================================================
//�S�`�揈���֐�
//=============================================================================
void CScene::DrawAll(void)
{

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				// �|���S���̍X�V����
				m_apScene[nCntPriority][nCntScene]->Draw();
			}
		}
	}
}
//=============================================================================
//�S�I�������֐�
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
//�I�������֐�
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
//�I�u�W�F�N�g�ݒ�֐�
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//=============================================================================
//�V�[�������֐�
//=============================================================================
CScene * CScene::GetScene(int nCnt)
{
	return m_apScene[0][nCnt];
}

