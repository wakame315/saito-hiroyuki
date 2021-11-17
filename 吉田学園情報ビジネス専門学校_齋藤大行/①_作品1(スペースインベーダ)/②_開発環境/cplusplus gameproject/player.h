//=============================================================================
//
// �v���C���[�̒�` [player.cpp]
// Author :�V����s
//
//=============================================================================

//=============================================================================
//��d�C���N���[�h�h�~
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"


//=============================================================================
//�}�N����`
//=============================================================================
#define PLAYER_MOVE 7.5f

//=============================================================================
// �N���X�錾
//=============================================================================
class CPlayer : public CScene2d//�v���C���[�N���X
{
public:
	typedef enum
	{
		PLAYERSTATE_NORMAL = 0,
		PLAYERSTATE_DAMAGE,
		PLAYERSTATE_CUA,
		PLAYERSTATE_MAX,
	}PLAYERSTATE;


	CPlayer();
	~CPlayer();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(int nDamage, int nHitType);
	//�ÓI�֐�
	static CPlayer *Create(D3DXVECTOR3 pos);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_playerVector;
	int m_nLife;
	int m_nCntState;
	int m_nBulletTime;
	bool m_bBulletChange;
	PLAYERSTATE m_playerstate;
	
};
#endif 
