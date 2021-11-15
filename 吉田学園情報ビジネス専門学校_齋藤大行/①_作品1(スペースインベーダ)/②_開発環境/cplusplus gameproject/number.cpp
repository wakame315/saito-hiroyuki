//=============================================================================
//
// �����̏��� [number.cpp]
// Author : �V����s
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h" 

//=============================================================================
//�ÓI�����o�[�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CNumber::CNumber()
{
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_nNumber = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CNumber::~CNumber()
{

}

//=============================================================================
//�e�N�X�`�����[�h�֐�
//=============================================================================
HRESULT CNumber::Load(void)
{
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_NAME13,					// �t�@�C���̖��O
		&m_pTexture);		// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
//�e�N�X�`���A�����[�h�֐�
//=============================================================================
void CNumber::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//���������֐�
//=============================================================================
CNumber * CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNum)
{
	CNumber * pNumber;			//�|�C���^
	pNumber = new CNumber;		//�C���X�^���X����
	pNumber->Init();			//����������
	pNumber->SetPosition(pos);	//�ʒu�ݒ�
	pNumber->SetSize(size);		//�T�C�Y�ݒ�
	pNumber->SetNumber(nNum);	//�����ݒ�
	
	return pNumber;
}

//=============================================================================
//�����������֐�
//=============================================================================
HRESULT CNumber::Init()
{
	m_nNumber = 0;

	// ���_�o�b�t�@�̐���
	if (FAILED(CManager::GetRenderer()->GetDevice()->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * MAX_SCENE,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
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
	pVtx[0].Pos = D3DXVECTOR3(m_pos.x + (-m_size.x / 2), m_pos.y + (-m_size.y / 2), 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(m_pos.x + ( m_size.x / 2), m_pos.y + (-m_size.y / 2), 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(m_pos.x + (-m_size.x / 2), m_pos.y + ( m_size.y / 2), 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(m_pos.x + ( m_size.x / 2), m_pos.y + ( m_size.y / 2), 0.0f);

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
void CNumber::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
//�X�V�����֐�
//=============================================================================
void CNumber::Update(void)
{
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].Pos = D3DXVECTOR3(m_pos.x + (-m_size.x / 2), m_pos.y + (-m_size.y / 2), 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (-m_size.y / 2), 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(m_pos.x + (-m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0.0f);

	pVtx[0].tex = D3DXVECTOR2(m_nNumber * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_nNumber * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_nNumber * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_nNumber * 0.1f + 0.1f, 1.0f);//�e�N�X�`�����W���X�V

	m_pVtxBuff->Unlock();
}

//=============================================================================
//�`�揈���֐�
//=============================================================================
void CNumber::Draw(void)
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
//�ʒu�ݒ�
//=============================================================================
void CNumber::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
//�T�C�Y�ݒ�
//=============================================================================
void CNumber::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
//�����ݒ�
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	m_nNumber = nNumber;
}
