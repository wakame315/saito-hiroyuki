//=============================================================================
//
// �V�[��2d��` [scene2d.cpp]
// Author :�V����s
//
//=============================================================================

//=============================================================================
//��d�C���N���[�h�h�~
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"


//=============================================================================
// �N���X�錾
//=============================================================================
class CScene2d : public CScene//�V�[��2d�N���X
{
public:
	CScene2d(int nPriority = 2);			//�R���g���N�^
    virtual~CScene2d();						//�f�X�g���N�^
	virtual HRESULT Init(void);				//����������
	virtual void Uninit(void);				//�I������			
	virtual void Update(void);				//�X�V����			
	virtual void Draw(void);				//�`�揈��			
	//�ÓI�֐�								
    void SetPosition(D3DXVECTOR3 pos);		//�ʒu�ݒ�
	D3DXVECTOR3 GetPosition(void);			//�ʒu����

	void SetMove(D3DXVECTOR3 move);			//�ړ��ʐݒ�
	D3DXVECTOR3 GetMove(void);				//�ړ��ʏ���
	
	void SetRot(D3DXVECTOR3 rot);			//�����ݒ�
	D3DXVECTOR3 GetRot(void);				//��������

	void SetSize(int Size_x, int Size_y);	//�T�C�Y�ݒ�
	void SetAnim(int nPatternAnim);			//�A�j���[�V�����ݒ�
	D3DXCOLOR GetClo(void);					//�F����
	void SetClo(D3DXCOLOR nClo);			//�F�ݒ�
	void SetTexture(void);					//�e�N�X�`���ݒ�
	static CScene2d *Create();				//��������
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);//�e�N�X�`�����蓖��

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				m_pos;          //�ʒu
	D3DXVECTOR3				m_rot;			// ����
	D3DXVECTOR3             m_move;			//�ړ���
	D3DXCOLOR               m_clo;			//�F
	D3DXCOLOR               m_clo_r;		//���b�h�l
	D3DXCOLOR               m_clo_g;		//�O���[���l
	D3DXCOLOR               m_clo_b;		//�u���[�l
	D3DXCOLOR               m_clo_a;		//�A���t�@�m
	int m_Size_x;							//�|���S����x�̕�
	int m_Size_y;							//�|���S����y�̕�
	int m_nPatternAnim;						//�A�j���[�V�����̃p�^�[��

};





#endif 
