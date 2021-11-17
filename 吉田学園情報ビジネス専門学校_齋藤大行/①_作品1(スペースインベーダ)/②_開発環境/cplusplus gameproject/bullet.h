//=============================================================================
//
// �e�̒�` [bullet.cpp]
// Author :�V����s
//
//=============================================================================

//=============================================================================
//��d�C���N���[�h�h�~
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_
#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �N���X�錾
//=============================================================================
class CBullet : public CScene2d//�e�N���X
{
public:
	//==============================================
	//�񋓌^�錾
	//==============================================
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
	void CollisionBullet(D3DXVECTOR3 pos);	//�e�̓����蔻��
	void CreateExplosion(D3DXVECTOR3 pos);

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
