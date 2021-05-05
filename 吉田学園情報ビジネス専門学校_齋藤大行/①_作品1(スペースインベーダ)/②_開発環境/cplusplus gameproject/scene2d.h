#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"

//*********************************************************
// �O���錾
//*********************************************************

//�I�u�W�F�N�g�N���X
class CScene2d : public CScene
{
public:
	CScene2d(int nPriority = 2);
    virtual~CScene2d();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	//�ÓI�֐�
    void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);

	void SetMove(D3DXVECTOR3 move);
	D3DXVECTOR3 GetMove(void);
	
	void SetRot(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRot(void);

	void SetSize(int Size_x, int Size_y);
	void SetAnim(int nPatternAnim);
	D3DXCOLOR GetClo(void);
	void SetClo(D3DXCOLOR nClo);
	void SetTexture(void);
	void SetTexture(int textpos);
	static CScene2d *Create();
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

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

};





#endif 
