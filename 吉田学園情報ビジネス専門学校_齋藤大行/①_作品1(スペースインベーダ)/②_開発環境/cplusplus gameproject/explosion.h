//=============================================================================
//
// �����̒�` [explosion.cpp]
// Author :�V����s
//
//=============================================================================

//=============================================================================
//��d�C���N���[�h�h�~
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#define _CRT_SECURE_NO_WARNINGS



//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

class CExplosion : public CScene2d//�����N���X
{
public:
	//==============================================
	//�񋓌^�錾
	//==============================================
	typedef enum
	{
		EXPLOSION_NORMAL = 0,
		EXPLOSION_BULLET,
		EXPLOSION_CHARACTER,
		ENEMYSTATE_MAX,
	}EXPLOSION;


	CExplosion();																			//�R���g���N�^
	~CExplosion();																			//�f�X�g���N�^
	static HRESULT Load(void);
	static void Unload(void);
	static CExplosion *Create(D3DXVECTOR3 pos , D3DXCOLOR clo, int nSize ,EXPLOSION type);	//�쐬����
	HRESULT Init(EXPLOSION type);															//����������
	void Uninit(void);																		//�I������
	void Update(void);																		//�X�V����
	void Draw(void);																		//�`�揈��
	int GetPatternAnim(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_EXPLOSION_TEXTURE];
	int m_nCounterAnim;//�J�E���^�[
	int m_nPatternAnim;//�p�^�[��NO
protected:


};

#endif
