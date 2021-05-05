#include "explosion.h"
#include "scene2d.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "main.h"
#include "bullet.h"
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture[MAX_EXPLOSION_TEXTURE] = {};

CExplosion::CExplosion():CScene2d(3)
{
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

CExplosion::~CExplosion()
{
}

HRESULT CExplosion::Load(void)
{
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),			// �f�o�C�X�ւ̃|�C���^
	TEXTURE_NAME3,															// �t�@�C���̖��O
	&m_pTexture[EXPLOSION_BULLET]);														// �ǂݍ��ރ������[

																			// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),			// �f�o�C�X�ւ̃|�C���^
	TEXTURE_NAME5,															// �t�@�C���̖��O
	&m_pTexture[EXPLOSION_CHARACTER]);

	return S_OK;
}

void CExplosion::Unload(void)
{
	for (int nCount = 0; nCount < MAX_EXPLOSION_TEXTURE; nCount++)
	{
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

CExplosion * CExplosion::Create(D3DXVECTOR3 pos, D3DXCOLOR clo, int nSize, EXPLOSION type)
{
	CExplosion * pExplosion;
	pExplosion = new CExplosion;
	pExplosion->Init(type);
	pExplosion->SetClo(clo);
	pExplosion->SetPosition(pos);
	pExplosion->SetSize(nSize, nSize);
	
	return pExplosion;
}

HRESULT CExplosion::Init(EXPLOSION type)
{
	CScene2d::Init();
	CScene2d::BindTexture(m_pTexture[type]);
	
	return S_OK;
}

void CExplosion::Uninit(void)
{
	CScene2d::Uninit();
}

void CExplosion::Update(void)
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	EXPLOSION type;

	pos = GetPosition();
	move = GetMove();

	

		m_nCounterAnim++;

		if (m_nCounterAnim >= 4)
		{
			m_nCounterAnim = 0;//�J�E���^�[�����l�ɖ߂�
			m_nPatternAnim++;


			SetAnim(m_nPatternAnim);
			

			SetPosition(pos);
		

			CScene2d::Update();
	

			if (m_nPatternAnim >= 8)
			{
				m_nPatternAnim = 0;
				Uninit();
			}

		}
}

void CExplosion::Draw(void)
{
	CScene2d::Draw();
}

int CExplosion::GetPatternAnim(void)
{
	return m_nPatternAnim;
}
