//=============================================================================
//
// �������� [explosion.cpp]
// Author :�V����s
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "explosion.h"
#include "scene2d.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "main.h"
#include "bullet.h"

//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture[MAX_EXPLOSION_TEXTURE] = {};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CExplosion::CExplosion():CScene2d(3)
{
	m_nCounterAnim = 0;//�A�j���[�V�����J�E���g
	m_nPatternAnim = 0;//�A�j���[�V�����p�^�[��
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CExplosion::~CExplosion()
{
}

//=============================================================================
//�e�N�X�`�����[�h�֐�
//=============================================================================
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

//=============================================================================
//�e�N�X�`���A�����[�h�֐�
//=============================================================================
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

//=============================================================================
//���������֐�
//=============================================================================
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, D3DXCOLOR clo, int nSize, EXPLOSION type)
{
	CExplosion * pExplosion;				   //�|�C���^
	pExplosion = new CExplosion;			   //�C���X�^���X����
	pExplosion->Init(type);					   //����������
	pExplosion->SetClo(clo);				   //�F�ݒ�
	pExplosion->SetPosition(pos);			   //�ʒu�ݒ�
	pExplosion->SetSize(nSize, nSize);		   //�T�C�Y�ݒ�
											   
	return pExplosion;
}

//=============================================================================
//�����������֐�
//=============================================================================
HRESULT CExplosion::Init(EXPLOSION type)
{
	CScene2d::Init();
	CScene2d::BindTexture(m_pTexture[type]);
	
	return S_OK;
}

//=============================================================================
//�I�������֐�
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//�X�V�����֐�
//=============================================================================
void CExplosion::Update(void)
{
	D3DXVECTOR3 pos;			 //�ʒu
	D3DXVECTOR3 move;			 //�ړ���
	EXPLOSION type;				 //�^�C�v

	pos = GetPosition();		 //�ʒu����
	move = GetMove();			 //�ړ��ʏ���
								 
	//�A�j���[�V�����̃J�E���g
		m_nCounterAnim++;
			//�J�E���g��4�ɂȂ�����
		if (m_nCounterAnim >= 4)
		{
			m_nCounterAnim = 0;//�J�E���^�[�����l�ɖ߂�
			m_nPatternAnim++;//�p�^�[�����A��


			SetAnim(m_nPatternAnim);//�A�j���[�V�����̐ݒ�
			

			SetPosition(pos);//�ʒu�̐ݒ�
		

			CScene2d::Update(); //Scene2d��ǂݍ���
	
			//�p�^�[����8�ɂȂ�����
			if (m_nPatternAnim >= 8)
			{	//�[���ɖ߂�
				m_nPatternAnim = 0;
				//����������
				Uninit();
			}

		}
}

//=============================================================================
//�`�揈���֐�
//=============================================================================
void CExplosion::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
//^�A�j���[�V�����̃p�^�[������
//=============================================================================
int CExplosion::GetPatternAnim(void)
{
	return m_nPatternAnim;
}
