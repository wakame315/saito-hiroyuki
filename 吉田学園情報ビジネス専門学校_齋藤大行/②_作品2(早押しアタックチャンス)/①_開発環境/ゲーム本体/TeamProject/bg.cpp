//=============================================================================
//
// �w�i���� [bg.cpp]
// Author :�V����s
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "main.h"
#include "inputkeyboard.h"


//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CBg::m_pTexture[MAX_TEXTURE] = {};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CBg::CBg() :CScene(0)
{
	memset(m_apScene2d, 0, sizeof(m_apScene2d));
	m_bBgType = BG_TYPE_NONE;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CBg::~CBg()
{
}
//=============================================================================
//�e�N�X�`�����[�h�֐�
//=============================================================================
HRESULT CBg::Load(void)
{

	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_NAME3,					// �t�@�C���̖��O
		&m_pTexture[0]);									// �ǂݍ��ރ������[

															// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_NAME4,					// �t�@�C���̖��O
		&m_pTexture[1]);									// �ǂݍ��ރ������[

															// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_NAME5,					// �t�@�C���̖��O
		&m_pTexture[2]);									// �ǂݍ��ރ������[

	return S_OK;
}

void CBg::Unload(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		if (m_pTexture != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}

}
//=============================================================================
//���������֐�
//=============================================================================
CBg * CBg::Create(void)
{
	CBg * pBg;
	pBg = new CBg;
	pBg->Init();
	
	
	return pBg;
}

//=============================================================================
//�����������֐�
//=============================================================================
HRESULT CBg::Init(void)
{
		m_apScene2d[0] = new CScene2d;
		m_apScene2d[0]->Init();
		m_apScene2d[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		m_apScene2d[0]->SetClo(D3DXCOLOR(NONE_CLO, NONE_CLO, NONE_CLO, NONE_CLO));
		m_apScene2d[0]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		m_apScene2d[0]->SetObjType(TYPE_BG);
		m_apScene2d[0]->SetTexture();
		m_apScene2d[0]->BindTexture(m_pTexture[0]);
		m_apScene2d[0]->SetDraw(false);
		m_bBgType = BG_TYPE1;
	
	for (int nCount = 1; nCount < MAX_TEXTURE; nCount++)
	{
		if (nCount == 1)
		{
			m_apScene2d[nCount] = new CScene2d;
			m_apScene2d[nCount]->Init();
			m_apScene2d[nCount]->SetPosition(D3DXVECTOR3(350.0f, 520.0f, 0.0f));
			m_apScene2d[nCount]->SetClo(D3DXCOLOR(NONE_CLO, NONE_CLO, NONE_CLO, NONE_CLO));
			m_apScene2d[nCount]->SetObjType(TYPE_BG);
			m_apScene2d[nCount]->SetSize(200.f, 400.0f);
			m_apScene2d[nCount]->SetTexture();
			m_apScene2d[nCount]->BindTexture(m_pTexture[nCount]);
			m_apScene2d[nCount]->SetDraw(false);
			m_bBgType = BG_TYPE2;
		}
		else if (nCount == 2)
		{
			m_apScene2d[nCount] = new CScene2d;
			m_apScene2d[nCount]->Init();
			m_apScene2d[nCount]->SetPosition(D3DXVECTOR3(850.0f, 520.0f, 0.0f));
			m_apScene2d[nCount]->SetClo(D3DXCOLOR(NONE_CLO, NONE_CLO, NONE_CLO, NONE_CLO));
			m_apScene2d[nCount]->SetObjType(TYPE_BG);
			m_apScene2d[nCount]->SetSize(200.f, 400.0f);
			m_apScene2d[nCount]->SetTexture();
			m_apScene2d[nCount]->BindTexture(m_pTexture[nCount]);
			m_apScene2d[nCount]->SetDraw(false);
			m_bBgType = BG_TYPE3;
		}
			
	}

	return S_OK;
}

//=============================================================================
//�I�������֐�
//=============================================================================
void CBg::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		m_apScene2d[nCount]->Uninit();
		m_apScene2d[nCount] = NULL;
	}

	Release();
}
//=============================================================================
//�X�V�����֐�
//=============================================================================
void CBg::Update(void)
{

	CInputKeyboard *pKey;

	pKey = CManager::GetInputKeyboard();

	if (pKey->GetkeyboardRelease(DIK_SPACE) == true)
	{
		m_apScene2d[2]->SetDraw(true);
	}
}
//=============================================================================
//�`�揈���֐�
//=============================================================================
void CBg::Draw(void)
{
	
}
//=============================================================================
//�^�C�v�����֐�
//=============================================================================
CBg::BGTYPE CBg::GetBG(void)
{
	return m_bBgType;
}
