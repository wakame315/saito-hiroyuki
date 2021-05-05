#include "score.h"
#include "main.h"


CScore::CScore():CScene(4)
{
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_nScore = 0;
}

CScore::~CScore()
{
}

CScore * CScore::Create(void)
{
	CScore * pScore;
	pScore = new CScore;
	pScore->Init();
	pScore->SetObjType(TYPE_SCORE);
	return pScore;
}

HRESULT CScore::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
	{
 		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(SCREEN_WIDTH - nCnt * NUM_SIZE_X - NUM_SIZE_X / 2, NUM_SIZE_Y / 2, 0.0f), D3DXVECTOR3(NUM_SIZE_X, NUM_SIZE_Y, 0.0f), 0);
	}

	m_nScore = 0;
	
	return S_OK;
}

void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = NULL;
		}
	}

	Release();
}

void CScore::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Update();
		}
	}

	//SetScore(m_nScore);
}

void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Draw();
		}
	}

}

void CScore::SetScore(int nScore)
{
	m_nScore = nScore;

	for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->SetNumber(m_nScore % (int)pow(10, nCnt + 1) / (int)pow(10, nCnt));
		}
	}
}

void CScore::AddScore(int nScore)
{
	m_nScore += nScore;

	for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->SetNumber(m_nScore % (int)pow(10, nCnt + 1) / (int)pow(10, nCnt));
		}
	}
}
