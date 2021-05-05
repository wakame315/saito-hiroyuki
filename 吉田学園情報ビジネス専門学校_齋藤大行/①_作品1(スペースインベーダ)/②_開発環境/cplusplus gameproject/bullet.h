//=============================================================================
//
// DirectX���^���� [bullet.cpp]
// Author :�V����s
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

class CBullet : public CScene2d
{
public:
	typedef enum
	{
		BULLET_TYPE_NONE = 0,
		BULLET_TYPE_1,
		BULLET_TYPE_2,
		BULLET_TYPE_ENEMY,
		BULLET_TYPE_MAX,
	}BULLETTYPE;

	CBullet();					//�R���g���N�^
	~CBullet();					//�f�X�g���N�^
	static HRESULT Load(void);
	static void Unload(void);
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nSize, int nLife, D3DXCOLOR col, BULLETTYPE type);	//�쐬����
	HRESULT Init(BULLETTYPE type);				//����������
	void Uninit(void);			//�I������
	void Update(void);			//�X�V����
	void Draw(void);			//�`�揈��
private:
	D3DXVECTOR3 m_move;//�ړ���
	static LPDIRECT3DTEXTURE9 m_pTexture[MAXBULLET];
	int m_nlife;
	int m_nBulletDamage;
	bool m_bHit;
	BULLETTYPE m_BulletType;
protected:



};

#endif
