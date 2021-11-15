//=============================================================================
//
// �V�[��2D���� [scene2d.cpp]
// Author : �V����s
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "inputkeyboard.h"
#include "explosion.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CScene2d::CScene2d(int nPriority):CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_Size_x = 0;
	m_Size_y = 0;
	m_pTexture = 0;
	m_pVtxBuff = 0;

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScene2d::~CScene2d()
{
}

//=============================================================================
//�����������֐�
//=============================================================================
HRESULT CScene2d::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	


	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * MAX_SCENE,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,				// ���_�o�b�t�@�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].Pos = D3DXVECTOR3(m_pos.x + (-POLYGON_SIZE_Y / 2), m_pos.y + (-POLYGON_SIZE_Y / 2), 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(m_pos.x + ( POLYGON_SIZE_X / 2), m_pos.y + (-POLYGON_SIZE_Y / 2), 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(m_pos.x + (-POLYGON_SIZE_X / 2), m_pos.y + ( POLYGON_SIZE_Y / 2), 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(m_pos.x + ( POLYGON_SIZE_X / 2), m_pos.y + ( POLYGON_SIZE_Y / 2), 0.0f);

	//rhwn�̐ݒ�i�l��1.0�ŌŒ�j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�̃J���[(0�`255�͈̔͂Őݒ�)
	pVtx[0].clo = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].clo = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].clo = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].clo = D3DCOLOR_RGBA(255, 255, 255, 255);

	m_pVtxBuff->Unlock();


	return S_OK;
}

//=============================================================================
//�I�������֐�
//=============================================================================
void CScene2d::Uninit(void)
{

	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�I�u�W�F�N�g�j��
	Release();
}

void CScene2d::Update(void)
{

	//���_����ݒ�
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].Pos = D3DXVECTOR3(m_pos.x - (m_Size_x / 2), m_pos.y - (m_Size_y / 2), 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(m_pos.x + (m_Size_x / 2), m_pos.y - (m_Size_y / 2), 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(m_pos.x - (m_Size_x / 2), m_pos.y + (m_Size_y / 2), 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(m_pos.x + (m_Size_x / 2), m_pos.y + (m_Size_y / 2), 0.0f);

	//���_�̃J���[(0�`255�͈̔͂Őݒ�)
	pVtx[0].clo = D3DCOLOR_RGBA(m_clo_r,m_clo_g,m_clo_b,m_clo_a);
	pVtx[1].clo = D3DCOLOR_RGBA(m_clo_r,m_clo_g,m_clo_b,m_clo_a);
	pVtx[2].clo = D3DCOLOR_RGBA(m_clo_r,m_clo_g,m_clo_b,m_clo_a);
	pVtx[3].clo = D3DCOLOR_RGBA(m_clo_r,m_clo_g,m_clo_b,m_clo_a);

	m_pVtxBuff->Unlock();
}

//=============================================================================
//�`�揈���֐�
//=============================================================================
void CScene2d::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}


//=============================================================================
//�ʒu�ݒ�֐�
//=============================================================================
void CScene2d::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
//�ʒu�����֐�
//=============================================================================
D3DXVECTOR3 CScene2d::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
//�ړ��ʐݒ�֐�
//=============================================================================
void CScene2d::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
//�ړ��ʏ����֐�
//=============================================================================
D3DXVECTOR3 CScene2d::GetMove(void)
{
	return m_move;
}

//=============================================================================
//�����ݒ�֐�
//=============================================================================
void CScene2d::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
//���������֐�
//=============================================================================
D3DXVECTOR3 CScene2d::GetRot(void)
{
	return m_rot;
}

//=============================================================================
//�T�C�Y�ݒ�֐�
//=============================================================================
void CScene2d::SetSize(int Size_x, int Size_y)
{
	m_Size_x = Size_x;
	m_Size_y = Size_y;
}

//=============================================================================
//�A�j���[�V�����ݒ�֐�
//=============================================================================
void CScene2d::SetAnim(int nPatternAnim)
{
	m_nPatternAnim = nPatternAnim;
	
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
		pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.09f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.09f + 0.09f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.09f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.09f + 0.09f, 1.0f);//�e�N�X�`�����W���X�V

	m_pVtxBuff->Unlock();
}

//=============================================================================
//�F�����֐�
//=============================================================================
D3DXCOLOR CScene2d::GetClo(void)
{
   	return m_clo;
}

//=============================================================================
//�F�ݒ�֐�
//=============================================================================
void CScene2d::SetClo(D3DXCOLOR nClo)
{
	m_clo_r = nClo.r;
	m_clo_g = nClo.g;
	m_clo_b = nClo.b;
	m_clo_a = nClo.a;
}

//=============================================================================
//�e�N�X�`���ݒ�֐�
//=============================================================================
void CScene2d::SetTexture(void)
{
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();

}


//=============================================================================
//���������֐�
//=============================================================================
CScene2d *CScene2d::Create()
{
	CScene2d * pScene2d;
	pScene2d = new CScene2d;
	pScene2d->Init();
	return pScene2d;
}

//=============================================================================
//�e�N�X�`�����蓖��
//=============================================================================
void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

