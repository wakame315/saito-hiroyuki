//=============================================================================
//
// DirectX���^���� [bg.cpp]
// Author :�V����s
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TEXTURE 3

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

class CBg : public CScene
{
public:
	CBg();					//�R���g���N�^
	~CBg();					//�f�X�g���N�^
	static HRESULT Load(void);
	static void Unload(void);
	static CBg *Create(void);	//�쐬����
	HRESULT Init(void);				//����������
	void Uninit(void);			//�I������
	void Update(void);			//�X�V����
	void Draw(void);			//�`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];
	CScene2d *m_apScene2d[MAX_SCENE];
protected:


};

#endif
