//=============================================================================
//
// �G�̒�` [enemy.cpp]
// Author :�V����s
//
//=============================================================================

//=============================================================================
//��d�C���N���[�h�h�~
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �N���X�錾
//=============================================================================
class CEnemy : public CScene2d//�G�N���X
{
public:

	//==============================================
	//�񋓌^�錾
	//==============================================
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
	ENEMYSTATE_NORMAL = 0,//�G�̏��
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
	void Hit(int nDamage , ENEMYTYPE type ,int nHitType);//�e�������������̏���
	void SetEnemyType(ENEMYTYPE Type);					 //�G�̃^�C�v�̐ݒ�
	void AttackType(ENEMYTYPE Type);					 //�U���̃p�^�[��	 
	ENEMYTYPE GetEnemyType(void) {return m_enemyType;}	 //�o�������G�̐���������
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_ENEMY];//�e�N�X�`��
	static int m_nEnemyNum;							//�o����
	static int m_nEnemySpawnState;					//�X�|�[������܂ł̎���
	static int m_nEnemydesu;						//�|������
	bool m_bEnemydeath;								//���񂾂��ǂ���
	int m_nlife;									//���C�t
													
	int m_nCntState;								//��Ԉڍs�̃J�E���g
	int m_nScoreUp;									//�X�R�A�㏸��
	int m_nTrue;									//�ړ������ύX�̔���
	
	ENEMYTYPE m_enemyType;							//�^�C�v
	ENEMYSTATE m_enemyState;						//���


protected:


};

#endif
