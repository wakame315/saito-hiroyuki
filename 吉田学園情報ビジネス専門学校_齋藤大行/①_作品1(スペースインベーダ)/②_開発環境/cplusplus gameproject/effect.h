//=============================================================================
//
// DirectX���^���� [effect.cpp]
// Author :�V����s
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

class CEffect : public CScene2d
{
public:
	CEffect();					//�R���g���N�^
	~CEffect();					//�f�X�g���N�^
	static HRESULT Load(void);
	static void Unload(void);
	static CEffect *Create(D3DXVECTOR3 pos, int nSize_X, int nSize_Y);	//�쐬����
	HRESULT Init();				//����������
	void Uninit(void);			//�I������
	void Update(void);			//�X�V����
	void Draw(void);			//�`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[2];
	
protected:


};

#endif
