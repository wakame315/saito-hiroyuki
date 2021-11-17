//=============================================================================
//
// �|���S����` [polygon.h]
// Author : �V����s
//
//=============================================================================

//=============================================================================
//��d�C���N���[�h�h�~
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CPolygon : public CScene2d//�|���S���N���X
{
public:
	typedef enum
	{
		TEX_SIGNAL_NONE,
		TEX_SIGNAL_GO,
		TEX_SIGNAL_MISS,
	}TEX_SIGNAL;

	CPolygon();																		//�R���X�g���N�^
	~CPolygon();																	//�f�X�g���N�^
	static HRESULT Load(void);														//�e�N�X�`�����[�h
	static void Unload(void);														//�e�N�X�`���A�����[�h
	HRESULT Init(TEX_SIGNAL signal);												//����������
	void Uninit(void);																//�I������
	void Update(void);																//�X�V����
	void Draw(void);																//�`�揈��
	void SetTexSignal(TEX_SIGNAL signal);											//���}�̃e�N�X�`���ݒ�
	bool SetbUse(bool bUse);														//���}���g�����ǂ����ݒ�
	TEX_SIGNAL GetTexSignal(void) { return m_tSignal; }								//���}�̏���
	bool GetUse(void);																//���}���g���Ă��邩����
	int GetRandom(void);															//�����̏���
		
	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEX_SIGNAL signal);	//��������
	
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_SIGNAL];								//�e�N�X�`���̃|�C���^
	TEX_SIGNAL m_tSignal;															//���}�̎��
	bool m_buse;																	//�g���Ă��邩
	int m_nUseNum;																	//���}�̕\������
	int m_nOnePlay;																	//��x�����ǂݍ��ނ��߂̃t���O
};
#endif 
