//=============================================================================
//
// DirectX���^���� [life.cpp]
// Author :�V����s
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "scene2d.h"


class CLife : public CScene
{
public:
	CLife();					//�R���g���N�^
	~CLife();					//�f�X�g���N�^
	static HRESULT Load(void);
	static void Unload(void);
	static CLife *Create(void);	//�쐬����
	HRESULT Init();				//����������
	void Uninit(void);			//�I������
	void Update(void);			//�X�V����
	void Draw(void);			//�`�揈��
	void lifeMode(int Damage);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	CScene2d *m_apScene2d[PLAYER_MAX_LIFE];
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;          //�ʒu
	D3DXVECTOR3				m_size;          //�ʒu
	static int				m_life;
	
protected:


};

#endif
