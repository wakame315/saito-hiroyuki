//=============================================================================
//
// DirectX���^���� [enemy.cpp]
// Author :�V����s
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "scene2d.h"


class CEnemy : public CScene2d
{
public:

typedef enum
{ 
	ENEMY_TYPE1 = 0,		//�G�̎��
	ENEMY_TYPE2,		
	ENEMY_TYPE3,
	ENEMY_TYPE4,
	ENEMY_TYPE5,
	ENEMY_TYPE6,
	ENEMY_TYPE_MAX,
}ENEMYTYPE;
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMAGE,
	ENEMYSTATE_CUA,
	ENEMYSTATE_MAX,
}ENEMYSTATE;


	CEnemy();					//�R���g���N�^
	~CEnemy();					//�f�X�g���N�^
	static HRESULT Load(void);
	static void Unload(void);
	static CEnemy *Create(D3DXVECTOR3 pos, int nSize, int nLife, ENEMYTYPE Type);	//�쐬����
	static int GetNumEnemy(void);
	static void SetNumEnemy(int Num);
	static int GetEnemyDesu(void);
	static void SetEnemyDesu(int Numdesu);
	HRESULT Init(ENEMYTYPE Type);			//����������
	void Uninit(void);			//�I������
	void Update(void);			//�X�V����
	void Draw(void);			//�`�揈��
	void Hit(int nDamage , ENEMYTYPE type ,int nHitType);
	void SetEnemyType(ENEMYTYPE Type);
	void AttackType(ENEMYTYPE Type);
	ENEMYTYPE GetEnemyType(void) {return m_enemyType;}
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_ENEMY];
	static int m_nEnemyNum;
	static int m_nEnemySpawnState;
	static int m_nEnemydesu;
	bool m_bEnemydeath;
	int m_nlife;

	int m_nCntState;
	int m_nScoreUp;
	int m_nTrue;
	ENEMYTYPE n_nRandType;
	ENEMYTYPE m_enemyType;
	ENEMYSTATE m_enemyState;


protected:


};

#endif
