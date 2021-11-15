//=============================================================================
//
// �|���S������ [polygon.cpp]
// Author : �V����s
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "polygon.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "inputkeyboard.h"
#include "displaytime.h"
#include "main.h"
#include "sound.h"


//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CPolygon::m_pTexture[MAX_SIGNAL] = {};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CPolygon::CPolygon():CScene2d(2)
{
	m_tSignal = TEX_SIGNAL_NONE;//�����Ղ̏�����
	m_buse = false;//�t���O�̏�����
	m_nUseNum = 0;//���}�̐��l
	m_nOnePlay = 0;//��x�����̃t���O
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPolygon::~CPolygon()
{
}

//=============================================================================
//�e�N�X�`�����[�h
//=============================================================================
HRESULT CPolygon::Load(void)
{
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_NAME1,					// �t�@�C���̖��O
		&m_pTexture[0]);					// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_NAME2,					// �t�@�C���̖��O
		&m_pTexture[1]);					// �ǂݍ��ރ������[


	return S_OK;
}

//=============================================================================
//�e�N�X�`���A�����[�h
//=============================================================================
void CPolygon::Unload(void)
{
	for (int nCount = 0; nCount < MAX_SIGNAL; nCount++)
	{
		//�e�N�X�`���̊J��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
//�����������֐�
//=============================================================================
HRESULT CPolygon::Init(TEX_SIGNAL signal)
{
	CScene2d::Init();
	CScene2d::BindTexture(m_pTexture[signal - 1]);
	SetTexSignal(signal);
	GetRandom();
	m_buse = false;

	return S_OK;
}

//=============================================================================
//�I�������֐�
//=============================================================================
void CPolygon::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//�X�V�����֐�
//=============================================================================
void CPolygon::Update(void)
{
	//�L�[�{�[�h�̃|�C���^
	CInputKeyboard *pKey;
	pKey = CManager::GetInputKeyboard();

	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;

	//�e�N�X�`���ݒ�
	SetTexture();
	//�ꏊ������
	pos = GetPosition();
	//�p�x������
	rot = GetRot();
	//�T�E���h����
	CSound *pSound = CManager::GetSound();

	//�V�[����1�����Ă���
	for (int nCntScene = 0; nCntScene < MAX_POLYGON*PRIORITY_MAX; nCntScene++)
	{
		CScene *pScene = GetScene(nCntScene);
		CScene2d *pScene2d = (CScene2d*)pScene;
		//NULL�`�F�b�N
		if (pScene != NULL)
		{	//�^�C�v��TYPE_DISPLAYTIME�������ꍇ
			if (pScene->GetObjType() == TYPE_DISPLAYTIME)
			{
				//�o�ߎ��Ԃ������_���̐ݒ莞�Ԃ𒴂�����
				if (((CDisplaytime*)pScene)->GetTime() >= m_nUseNum)
				{	//���}������
					if (m_tSignal == TEX_SIGNAL_GO)
					{	//�t���O��0�Ȃ�
						if (m_nOnePlay == 0)
						{	//���ʉ����Đ�
							pSound->Play(CSound::SE_GO);
							//�t���O��1�ɂ���
							m_nOnePlay = 1;
						}
						//���}�̂��悤�t���O��true�ɂ���
						m_buse = true;
					}
					
					
				}
			}
		}
	}
	//�p�x�̐ݒ�
	SetRot(rot);

	//Scene2d�̍X�V��ǂݍ���
	CScene2d::Update();

}

//=============================================================================
//�`�揈��
//=============================================================================
void CPolygon::Draw(void)
{
	if (m_buse == true)
	{
		CScene2d::Draw();
	}
}

//=============================================================================
//�^�C�v���Ƃ̃e�N�X�`���ݒ�
//=============================================================================
void CPolygon::SetTexSignal(TEX_SIGNAL Type)
{
	m_tSignal = Type;
}

//=============================================================================
//���}�̎g�p�t���O�̐ݒ�֐�
//=============================================================================
bool CPolygon::SetbUse(bool bUse)
{
	m_buse = bUse;

	return m_buse;
}

//=============================================================================
//���������֐�
//=============================================================================
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

//=============================================================================
//���}�̎g�p�t���O�̐ݒ�֐�
//=============================================================================
bool CPolygon::GetUse(void)
{
	return m_buse;
}

//=============================================================================
//���������֐�
//=============================================================================
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