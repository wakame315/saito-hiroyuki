//=============================================================================
//
// �V�[��2d��` [scene2d.h]
// Author : �V����s
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"



//=============================================================================
// �N���X��`
//=============================================================================
class CScene2d : public CScene
{
public:
	CScene2d(int nPriority = 2);
	~CScene2d();
	HRESULT Init(void);					            //����������
	void Uninit(void);					            //�I������
	void Update(void);					            //�X�V����
	void Draw(void);					            //�`�揈��
	//�ÓI�֐�							            
	void SetPosition(D3DXVECTOR3 pos);	            //�ʒu�ݒ�
	D3DXVECTOR3 GetPosition(void);		            //�ʒu����
										         
	void SetMove(D3DXVECTOR3 move);		            //�ړ��ʐݒ�
	D3DXVECTOR3 GetMove(void);			            //�ړ��ʐݒ�
										          
	void SetRot(D3DXVECTOR3 rot);		            //�����ݒ�
	D3DXVECTOR3 GetRot(void);			            //��������
												
	void SetSize(int Size_x, int Size_y);			//�T�C�Y�ݒ�
	void SetAnim(int nPatternAnim);					//�A�j���[�V�����ݒ�
	D3DXCOLOR GetClo(void);							//�F����
	void SetClo(D3DXCOLOR nClo);					//�F�ݒ�
	void SetTexture(void);							//�e�N�X�`���ݒ�
	bool GetDraw(void);								//�`��ݒ�
	void SetDraw(bool DrawUse);						//�`�揊��
	static CScene2d *Create();						//��������
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//�e�N�X�`�����蓖��

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				m_pos;          //�ʒu
	D3DXVECTOR3				m_rot;			// ����
	D3DXVECTOR3             m_move;
	D3DXCOLOR               m_clo;
	D3DXCOLOR               m_clo_r;
	D3DXCOLOR               m_clo_g;
	D3DXCOLOR               m_clo_b;
	D3DXCOLOR               m_clo_a;
	int m_Size_x;							//�|���S����x�̕�
	int m_Size_y;							//�|���S����y�̕�
	int m_nPatternAnim;
	bool m_bDraw;

};





#endif 
