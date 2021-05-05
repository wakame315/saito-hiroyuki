#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene2d.h"

//*********************************************************
// �O���錾
//*********************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_MOVE 7.5f

 //
//�I�u�W�F�N�g�N���X
class CPlayer : public CScene2d
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
